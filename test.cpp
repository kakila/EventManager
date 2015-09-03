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
void TestObserver::update(const event_t& ev)
 {
     m_wasCalled = true;
}
bool TestObserver::wasCalled()
{
    return m_wasCalled;
}

void TestObserver::reset()
{
    m_wasCalled = false;
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

int main()
{
  inputManager& buttonManager = inputManager::getInstance();

  TestObserver observers[MAX_OBSERVERS] {};

  cout << "First load" << endl;
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    buttonManager.bind(observers[i], event_t::N);
  }
  buttonManager.notify();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertTrue(observers[i].wasCalled(), std::string("First Assert Failed: Observer ") + std::to_string(i) + std::string(" was not called!"));
    observers[i].reset();
  }

  pressed = false;
  buttonManager.notify();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertFalse(observers[i].wasCalled(), std::string("Second Assert Failed: Observer ") + std::to_string(i) + std::string(" was called but it wasn't supposed to!"));
    observers[i].reset();
  }

  cout << endl;
  cout << "Reset and reload" << endl;
  buttonManager.reset();
  pressed = true;

  buttonManager.notify();
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    assertFalse(observers[i].wasCalled(), std::string("Third Assert Failed: Observer ") + std::to_string(i) + std::string(" was called but it wasn't supposed to"));
    observers[i].reset();
  }

  //Bind all except number 3
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    buttonManager.bind(observers[i], event_t::N);
  }
  buttonManager.unbind(observers[3], event_t::N);
  buttonManager.notify();

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

  //Test dangerous stuff
  buttonManager.reset();
  buttonManager.reset();
  buttonManager.unbind(observers[0], event_t::N);

  cout << "All tests successful" << endl;
  return 0;
/*  buttonManager.bind(Obs0, event_t::N);
  buttonManager.bind(Obs0, event_t::W);
  buttonManager.bind(Obs1, event_t::N);
  buttonManager.bind(Obs1, event_t::W);

  buttonManager.notify();

  cout << endl;
  cout << "Unbind" << endl;
  buttonManager.unbind(Obs0, event_t::N); buttonManager.unbind(Obs0, event_t::N);
  buttonManager.unbind(Obs0, event_t::W);
  buttonManager.unbind(Obs1, event_t::N);

  buttonManager.notify();

  cout << endl;
  cout << "Reconfigure" << endl;
  buttonManager.bind(Obs0, event_t::W);
  buttonManager.bind(Obs0, event_t::E);
  buttonManager.bind(Obs1, event_t::S);

  buttonManager.notify();

  return 0;*/
}
