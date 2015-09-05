/*
 * test.cpp
 *
 * Copyright (C) 2015 - Juanpi Carbajal <ajuanpi+dev@gmail.com>
 * Copyright (C) 2015 - Ezequiel Pozzo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "test.h"
#include "string"

TestObserver::TestObserver()
{
    static int id = 0; _id = id++;
}
void TestObserver::notify(const Event & ev)
 {
     m_wasCalled = true;
     cout << "Event type: " << int(ev.get_type()) << endl;
}
bool TestObserver::wasCalled()
{
    return m_wasCalled;
}

void TestObserver::reset()
{
    m_wasCalled = false;
}

template<class T>
bool TestEventPublisher<T>::is_triggered()
{
  if (digitalRead(SW_S) == PRESSED)
    return true;
  return false;
}

template<class T>
const T& TestEventPublisher<T>::get_event() const
{
  return event;
}

void assertTrue(bool condition, std::string message)
{
    if (!condition)
    {
        cout<<message<< endl;
        exit(1);
    }
}

void assertFalse(bool condition, std::string message)
{
    assertTrue(!condition, message);
}

bool testSinglePublisher()
{
  inputManager& buttonManager = inputManager::getInstance();
  TestObserver observers[MAX_OBSERVERS] {};

  TestEventPublisher<TestEvent1> publisher1;

  cout << "First load" << endl;
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    buttonManager.bind(observers[i], publisher1);
  }
  buttonManager.update();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertTrue(observers[i].wasCalled(), std::string("First Assert Failed: Observer ") + std::to_string(i) + std::string(" was not called!"));
    observers[i].reset();
  }

  pressed = false;
  buttonManager.update();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertFalse(observers[i].wasCalled(), std::string("Second Assert Failed: Observer ") + std::to_string(i) + std::string(" was called but it wasn't supposed to!"));
    observers[i].reset();
  }

  cout << endl;
  cout << "Reset and reload" << endl;
  buttonManager.clear();
  pressed = true;

  buttonManager.update();
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertFalse(observers[i].wasCalled(), std::string("Third Assert Failed: Observer ") + std::to_string(i) + std::string(" was called but it wasn't supposed to"));
    observers[i].reset();
  }

  //Bind all except number 3
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    buttonManager.bind(observers[i], publisher1);
  }
  buttonManager.unbind(observers[3], publisher1);
  buttonManager.update();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    if (i == 3)
    {
      assertFalse(observers[i].wasCalled(), std::string("Fourth Assert Failed: Observer ") + std::to_string(i) + std::string(" was called but it wasn't supposed to!"));
    }
    else
    {
      assertTrue(observers[i].wasCalled(), std::string("Fourth Assert Failed: Observer ") + std::to_string(i) + std::string(" wasn't called but it was supposed to!"));
    }
  }
  return true;
}
bool testDeleteWhenNotExists()
{
  inputManager& buttonManager = inputManager::getInstance();
  TestObserver observer {};
  TestEventPublisher<TestEvent1> publisher;
  buttonManager.clear();
  buttonManager.clear();
  buttonManager.unbind(observer, publisher);
  return true;
}
bool testMultiplePublishers()
{
  inputManager& buttonManager = inputManager::getInstance();
  TestObserver observers[MAX_OBSERVERS] {};

  TestEventPublisher<TestEvent1> publisher1;
  TestEventPublisher<TestEvent2> publisher2;

  cout << "First load" << endl;
  for (int i = 0; i<MAX_OBSERVERS; i+=2)
  {
    buttonManager.bind(observers[i], publisher1);
  }
  for (int i = 1; i<MAX_OBSERVERS; i+=2)
  {
    buttonManager.bind(observers[i], publisher2);
  }
  buttonManager.update();

  for (int i = 0; i<MAX_OBSERVERS; i+=2)
  {
    assertTrue(observers[i].wasCalled(), std::string("First Assert Failed: Observer ") + std::to_string(i) + std::string(" was not called"));
    observers[i].reset();
  }
  return true;
}
int main()
{
  inputManager& buttonManager = inputManager::getInstance();
  testSinglePublisher();
  buttonManager.clear();
  //Test dangerous stuff
  testDeleteWhenNotExists();
  testMultiplePublishers();
  cout << "All tests successful" << endl;
  return 0;
}
