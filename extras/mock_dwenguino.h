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

#ifndef mock_dwenguino_h
#define mock_dwenguino_h

#include <cinttypes>
#include <iostream>

using namespace std;

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define lowByte(w) ((unsigned char) ((w) & 0xff))
#define highByte(w) ((unsigned char) ((w) >> 8))

typedef unsigned char byte;

// LEDS
extern byte LEDS;
void showLEDS();

// Mapping of analog pins as digital I/O
static const uint8_t A0 = 24;
static const uint8_t A1 = 25;
static const uint8_t A2 = 26;
static const uint8_t A3 = 27;
static const uint8_t A4 = 28;
static const uint8_t A5 = 29;
static const uint8_t A6 = 30;
static const uint8_t A7 = 31;

// Buttons
static const uint8_t SW_C = 47;
static const uint8_t SW_N = 16;
static const uint8_t SW_E = 17;
static const uint8_t SW_S = 18;
static const uint8_t SW_W = 19;

#define PRESSED 1
#define NOT_PRESSED 0

extern bool pressed;
uint8_t digitalRead(uint8_t);

typedef unsigned char byte;
typedef unsigned short int word;

unsigned long millis();
void delay(unsigned long ms);
unsigned long millis();

// WMath.cpp
long map(long, long, long, long, long);

void initDwenguino();


class BufferedLCD
{
  const char *BL;
  bool is_on;

  public:
    void print(const int & x)   const {cout << (is_on?BL:"|") << x << "\33[0m" << endl;};
    void print(const char & x)  const {cout << (is_on?BL:"|") << x << "\33[0m" << endl;};
    void print(const char* x)   const {cout << (is_on?BL:"|") << x << "\33[0m" << endl;};
    void print(const float & x) const {cout << (is_on?BL:"|") << x << "\33[0m" << endl;};

    void backLightOn(){is_on=true;};
    void backLightOff(){is_on=false;};
    void clear(){};

  // Singelton pattern
  public:
    static BufferedLCD& getInstance()
    {
        static BufferedLCD instance; // Guaranteed to be destroyed, Instantiated on first use.
        return instance;
    }

   private:
     BufferedLCD(): BL("\33[7m"){};
};

extern BufferedLCD& dwenguinoLCD;


#endif
