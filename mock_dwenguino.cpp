/*
  Copyrigt (C) 2012  Erik Elmore <erik@ironsavior.net>
  Copyrigt (C) 2012  JuanPi Carbajal <ajunapi+dev@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Based on mock_arduino, adapted for the dwenguino

#include <sys/timeb.h>
#include "mock_dwenguino.h"


void showLEDS()
{
  for (unsigned int i = 1;  i < 8; i++)
    if (LEDS & (0b00000001 << i))
      cout << "*";
    else
      cout << "-";
  cout << int(LEDS) << endl;
}

timeb t_start;
unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){}
}

void initDwenguino() {
  ftime(&t_start);
  LEDS=0;
}

bool pressed = true;
uint8_t digitalRead(uint8_t pin)
{
// C++ doesn't have nonblocking IO
//    char x;
//    cin>>x;
//    switch (x)
//    {
//      case 'S': pressed = (SW_S == pin); break;
//      case 'N': pressed = (SW_N == pin); break;
//      case 'W': pressed = (SW_W == pin); break;
//      case 'E': pressed = (SW_E == pin); break;
//      case 'C': pressed = (SW_C == pin); break;
//    }
  return pressed?PRESSED:NOT_PRESSED;
}

BufferedLCD& dwenguinoLCD = BufferedLCD::getInstance();
