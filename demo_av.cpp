/*
 * demo_av.cpp
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
      const ButtonEvent & e = static_cast<const ButtonEvent &>(ev);
      for (unsigned int i=0; i<5; i++)
      {
        if (e.button[i])
          LEDS ^= pattern[i];
      }
}

ButtonOnPressingPublisher::ButtonOnPressingPublisher(): port({SW_N,SW_W,SW_S,SW_E,SW_C})
{
  event = new ButtonEvent();
}

bool ButtonOnPressingPublisher::is_triggered()
{
  bool x = false;
  ButtonEvent * ev = static_cast<ButtonEvent *>(event);
  for (unsigned int i=0; i<5; i++)
  {
    x |= (digitalRead(port[i]) == PRESSED);
    ev->button[i] = (digitalRead(port[i]) == PRESSED);
  }
  return x;
}

const Event &ButtonOnPressingPublisher::get_event() const
{
  return *event;
}

/////////////////////////////////////////////////////////////////////
ButtonListener on_pressed;
ButtonOnPressingPublisher is_pressed;

void setup()
{
  initDwenguino();
  dwenguinoManager.bind(on_pressed, is_pressed);
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
    dwenguinoManager.update();
  }
}

int main ()
{
  setup();
  while (true) {loop(); showLEDS();};
  return 0;
}
