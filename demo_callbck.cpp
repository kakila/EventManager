/*
 * demo_callbck.cpp
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

#include "demo_callbck.h"

void notify(const Event * ev)
{
    switch (ev->get_type())
    {
      case button_name::N: LEDS = LEDS ^ 0b10000000; break;
      case button_name::S: LEDS = LEDS ^ 0b00000001; break;
      case button_name::W: LEDS = LEDS ^ 0b00100000; break;
      case button_name::E: LEDS = LEDS ^ 0b00000100; break;
      case button_name::C: LEDS = LEDS ^ 0b00011000; break;
    }
}

ButtonOnPressingPublisher::ButtonOnPressingPublisher(button_name type)
{
  switch (type)
  {
    case button_name::N: port = SW_N; break;
    case button_name::W: port = SW_W; break;
    case button_name::S: port = SW_S; break;
    case button_name::E: port = SW_E; break;
    case button_name::C: port = SW_C; break;
  }
  event = new Event(type);
}

bool ButtonOnPressingPublisher::is_triggered()
{
  return (digitalRead(port) == PRESSED);
}

/////////////////////////////////////////////////////////////////////

callback ButtonListener = notify;
ButtonOnPressingPublisher is_N_pressed(button_name::N);
ButtonOnPressingPublisher is_S_pressed(button_name::S);
ButtonOnPressingPublisher is_W_pressed(button_name::W);
ButtonOnPressingPublisher is_E_pressed(button_name::E);
ButtonOnPressingPublisher is_C_pressed(button_name::C);

void setup()
{
  initDwenguino();
  c_dwenguinoManager.bind(ButtonListener, is_N_pressed);
  c_dwenguinoManager.bind(ButtonListener, is_S_pressed);
  c_dwenguinoManager.bind(ButtonListener, is_W_pressed);
  c_dwenguinoManager.bind(ButtonListener, is_E_pressed);
  c_dwenguinoManager.bind(ButtonListener, is_C_pressed);
  dwenguinoLCD.print("Reset!");
  delay(500);
  dwenguinoLCD.clear();
  LEDS = 0;
}

unsigned int sinceLast = 0;
void loop()
{
    if (millis()- sinceLast > 200)
    {
      sinceLast = millis();
      c_dwenguinoManager.update();
    }
}

#ifndef ARDUINO
int main ()
{
 // Not working in PC
  setup();
  while (true)
  {
    loop();
    showLEDS();
  }
  return 0;
}
#endif
