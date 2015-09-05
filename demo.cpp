/*
 * demo.cpp
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

#include "demo.h"

buttonEventType::buttonEventType(const event_t& b): Event(b)
{
  switch (b)
  {
    case event_t::N: port = SW_N; name = 'N'; break;
    case event_t::W: port = SW_W; name = 'W'; break;
    case event_t::S: port = SW_S; name = 'S'; break;
    case event_t::E: port = SW_E; name = 'E'; break;
    case event_t::C: port = SW_C; name = 'C'; break;
  }

}

void buttonAction::notify(const Event & ev)
{

    if (ev.get_type() == event_t::N)
      // Extra filter for contextual action
      cout << "Button pressed: N" << endl;
      // Extra filter to extend base class methods
      cout << "Button pressed: " <<
              static_cast<const buttonEventType&>(ev).get_name() << endl;

}

bool buttonOnPress::is_triggered()
{
  if (digitalRead(button.get_port()) == PRESSED)
    return true;
  return false;
}

const Event& buttonOnPress::get_event() const
{
  return button;
}

int main()
{
  // SETUP
  inputManager& manager = inputManager::getInstance();
  buttonAction tell_button;
  buttonOnPress N_press(event_t::N);

  manager.bind(tell_button, N_press);
  cout << "Press button [N,W,S,E,C]"<<endl;

  // LOOP
  char input;
  while (true)
  {
    cin >> input;
    pressed = false;
    if (input == 'N' || input == 'n')
      pressed = true;

    manager.update();
  }
  return 0;
}
