/*
 * test.cpp
 *
 * Copyright (C) 2015 - juanpi
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

bool pressed = true;
uint8_t mock_digitalRead(unsigned int pin)
{
    return pressed?PRESSED:NOT_PRESSED;
}

int main()
{
  inputManager& buttonManager = inputManager::getInstance(&mock_digitalRead);

  TestObserver observers[MAX_OBSERVERS] {};

  cout << "First load" << endl;
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    buttonManager.bind(observers[i], event_t::N);
  }
  buttonManager.notify();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    if (!observers[i].wasCalled())
    {
        cout<<"First Assert Failed: Observer " << i << " was not called!" << endl;
        return 1;
    }
    observers[i].reset();
  }

  pressed = false;
  buttonManager.notify();

  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    if (observers[i].wasCalled())
    {
        cout<<"Second Assert Failed: Observer " << i << " was called but it wasn't supposed to!" << endl;
        return 1;
    }
    observers[i].reset();
  }

  cout << endl;
  cout << "Reset and reload" << endl;
  buttonManager.reset();
  pressed = true;

  buttonManager.notify();
  for (int i = 0; i<MAX_OBSERVERS; i++)
  {
    if (observers[i].wasCalled())
    {
        cout<<"Third Assert Failed: Observer " << i << " was called but it wasn't supposed to!" << endl;
        return 1;
    }
  }
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
