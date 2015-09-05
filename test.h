/*
 * test.h
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

#include "inputManager.h"

class TestObserver: public observer_t {
  size_t _id;
  bool m_wasCalled = false;
  public:
    TestObserver();
    void notify(const Event& ev);
    bool wasCalled();
    void reset();
};

class TestEvent1: public Event
{
  // A dummy event class
  public:
    TestEvent1(): Event(1) {};
};

class TestEvent2: public Event
{
  // A dummy event class
  public:
    TestEvent2(): Event(2) {};
};

template<class T>
class TestEventPublisher: public Event_Publisher {
  bool m_trigger = false;
  T event;

  public:
  bool is_triggered();
  const T& get_event() const;
  void set_trigger(bool);

};

class TestInputManager : public inputManager {

};
