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

void ButtonListener::notify(const Event & ev)
{
    LEDS = LEDS?0:0b10000000;
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
}

bool ButtonOnPressingPublisher::is_triggered()
{
  return (digitalRead(port) == PRESSED);
}

const Event &ButtonOnPressingPublisher::get_event() const
{
  return *event;
}

ButtonListener tell_button;
ButtonOnPressingPublisher is_N_pressed(button_name::N);

void setup()
{
  initDwenguino();
  dwenguinoManager.bind(tell_button, is_N_pressed);
  dwenguinoLCD.backLightOn();
  dwenguinoLCD.print("Reset!");
  delay(500);
  dwenguinoLCD.clear();
  LEDS = 0;
}

unsigned int sinceLast = 0;
void loop()
{
  if (millis()- sinceLast > 100)
  {
    sinceLast = millis();
    dwenguinoManager.update();
  }
}

int main ()
{
  setup();
  while (true) {loop(); showLEDS();};
  return 0;
}
