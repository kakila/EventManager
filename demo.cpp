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

buttonType::buttonType(const char& b)
{
  name = b;
  switch (name)
  {
    case 'N': port = SW_N; break;
    case 'W': port = SW_W; break;
    case 'S': port = SW_S; break;
    case 'E': port = SW_E; break;
    case 'C': port = SW_C; break;
  }
}

void buttonAction::notify(const buttonType * ev)
{
     cout << "Button pressed: " << ev->get_name() << endl;
}

bool buttonOnPress::is_triggered()
{
  if (digitalRead(button.get_port()) == PRESSED)
    return true;
  return false;
}

const buttonType* buttonOnPress::get_event() const
{
  return &button;
}

int main()
{
  // SETUP
  inputManager& manager = inputManager::getInstance();
  buttonAction tell_button;
  buttonOnPress N_press('N');

  manager.bind(tell_button, N_press);
  cout << "Press button [N,W,S,E,C]"<<endl;

  // LOOP
  char input;
  while (true)
  {
    cin >> input;
    pressed = false;
    if (input == 'N')
      pressed = true;

    manager.update();
  }
  return 0;
}
