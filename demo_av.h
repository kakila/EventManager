/*
 * demo_av.h
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

#include <ObsPubManager.h>

enum button_name {N,W,S,E,C};

class ButtonEvent: public Event
{
  public:
    ButtonEvent(): Event(0){};
    bool button[5];
};

class ButtonListener: public EventObserver
{
  unsigned int pattern[5];
  public:
    ButtonListener(): pattern({0b10000000, 0b00100000, 0b00000001, 0b00000100, 0b00011000}) {};
    void notify(const Event & b);
};

class ButtonOnPressingPublisher: public EventPublisher
{
  Event *event;
  uint8_t port[5];
  public:
    ButtonOnPressingPublisher();
    bool is_triggered();
    const Event &get_event() const;
};
