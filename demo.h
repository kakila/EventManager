/*
 * demo.h
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
enum event_t : uint8_t {N,W,S,E,C};

class buttonEventType: public Event
{
  uint8_t port;
  char name;
  public:
    buttonEventType(const event_t& b);
    const uint8_t& get_port() const {return port;};
    const char& get_name() const {return name;};
};

class buttonAction: public observer_t
{
  public:
    buttonAction() {};
    void notify(const Event & b);
};

class buttonOnPress: public Event_Publisher
{
  buttonEventType button;
  public:
    buttonOnPress(const event_t& b): button(b){};
    bool is_triggered();
    const Event& get_event() const;
};
