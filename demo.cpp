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

ButtonPressingEvent::ButtonPressingEvent(const button_name& b): Event(b), name("Button n pressed")
{
  char button_name_char;
  switch (b)
  {
    case button_name::N: button_name_char = 'N'; port = SW_N; break;
    case button_name::W: button_name_char = 'W'; port = SW_W; break;
    case button_name::S: button_name_char = 'S'; port = SW_S; break;
    case button_name::E: button_name_char = 'E'; port = SW_E; break;
    case button_name::C: button_name_char = 'C'; port = SW_C; break;
  }
  name[7] = button_name_char;
}



void ButtonListener::notify(const Event & ev)
{
    if (ev.get_type() == button_name::N)
      // Extra filter for contextual action
      cout << "Button pressed: N" << endl;
}

//button_type(type),
ButtonOnPressingPublisher::ButtonOnPressingPublisher(ButtonPressingEvent type): event(&type)
{
//  switch (type)
//  {
//    case button_name::N: port = SW_N; break;
//    case button_name::W: port = SW_W; break;
//    case button_name::S: port = SW_S; break;
//    case button_name::E: port = SW_E; break;
//    case button_name::C: port = SW_C; break;
//  }
//  event = new ButtonPressingEvent(button_type);
}

bool ButtonOnPressingPublisher::is_triggered()
{
  return digitalRead(event->get_port()) == PRESSED;
}

const Event &ButtonOnPressingPublisher::get_event() const
{
  return *event;
}

int main()
{
  // SETUP
  inputManager& manager = inputManager::getInstance();
  ButtonListener tell_button;
//  ButtonOnPressingPublisher N_press(button_name::N);
  ButtonPressingEvent N_press(button_name::N);
  ButtonOnPressingPublisher is_N_pressed(N_press);

  manager.bind(tell_button, is_N_pressed);
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
