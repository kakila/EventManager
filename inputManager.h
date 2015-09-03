/*
 * inputManager.h
 *
 * Copyright (C) 2015 - juanpi
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


#ifndef inputManager_h
#define inputManager_h

//Commemt all these for Arduino
#include <cinttypes>
#define SW_N 15
#define SW_W 35
#define SW_S 5
#define SW_E 4
#define SW_C 1
#define PRESSED 1
#include <iostream>
using namespace std;
uint8_t digitalRead (unsigned int port);
//**

#ifndef MAX_OBS
#define MAX_OBSERVERS 10
#endif

#ifndef MAX_EVENTS
#define MAX_EVENTS 5
#endif

// FIXME: user defined events? So far MAX_EVENTS pased at compile time makes no sense.
enum event_t {N,W,S,E,C};
ostream& operator<<(ostream& os, const event_t& ev);

class observer_t {
  size_t _id;

  public:
    observer_t() { static int id = 0; _id = id++; }

    void update(const event_t& ev) {cout << "Observer " << _id << " catched event " << ev << endl;};
};

struct memoryNode {
  observer_t *obs = NULL;
  memoryNode *nxt[MAX_EVENTS] = {NULL};
};

class inputManager {
  memoryNode registered_observers[MAX_OBSERVERS];
  memoryNode *first_observer[MAX_EVENTS];

  size_t end;

  public:
    void bind(const observer_t& observer, const event_t& ev);
    void clear();
    void notify();

  private:
    size_t find(const observer_t* observer);

  // Singelton pattern
  public:
    static inputManager& getInstance()
    {
        static inputManager instance; // Guaranteed to be destroyed, Instantiated on first use.
        return instance;
    }

   private:
        inputManager() {end = 0;}; // Constructor? (the {} brackets) are needed here.
};

#endif
