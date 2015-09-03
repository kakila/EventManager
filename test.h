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
    void notify(const Event* ev);
    bool wasCalled();
    void reset();
};

class TestEvent: public Event {
  public:
    TestEvent(){};
    const int get_type() {return -1;};
};

class TestEventPub: public Event_Publisher {
  public:
    TestEventPub(){};
    bool is_triggered() {return false;};
    const Event* get_event(){return nullptr;};
};

class TestInputManager : public inputManager {

};
