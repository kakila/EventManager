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
enum button_name: uint8_t {N,W,S,E,C};

class ButtonPressingEvent: public Event
{
  button_name button;
  string name;
  uint8_t port;
  public:
    ButtonPressingEvent(const button_name& b);
    const button_name& get_button_name() const {return button;};
    const string get_name() const {return name;};
    const uint8_t get_port() const {return port;};
};

class ButtonListener: public IObserver
{
  public:
    ButtonListener() {};
    void notify(const Event & b);
};

class ButtonOnPressingPublisher: public Event_Publisher
{
//  button_name button_type;
//  Event *event;
//  uint8_t port;
  ButtonPressingEvent* event;
  public:
    //ButtonOnPressingPublisher(button_name type);
    ButtonOnPressingPublisher(ButtonPressingEvent type);
    bool is_triggered();
    const Event &get_event() const;
};
