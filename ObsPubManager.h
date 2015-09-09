/*
 * ObsPubManager.h
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


#ifndef ObsPubManager_h
#define ObsPubManager_h

#ifndef ARDUINO
#include "mock_dwenguino.h"
#else
#include <Dwenguino.h>
#endif

#ifndef MAX_OBS
#define MAX_OBSERVERS 10
#endif

#ifndef MAX_EVENTS
#define MAX_EVENTS 5
#endif

// Minimal Event interface
class Event
{
  uint8_t type;

  public:
    Event(const uint8_t & b): type(b) {};
    const uint8_t get_type() const {return type;};
};

// We do not want polymorphic destruction of these interfaces
// Protected destructors as in guideline #4
// http://www.gotw.ca/publications/mill18.htm
class EventPublisher {
  protected:
    ~EventPublisher() {};

  public:
    virtual bool is_triggered() = 0;
    virtual const Event &get_event() const = 0;
};

class EventObserver {
  protected:
    ~EventObserver() {}

  public:
    virtual void notify(const Event&) = 0;
};

class ObsPubManager {
  struct memoryNode {
    EventObserver *obs = nullptr;
    memoryNode *nxt = nullptr;
  };

  memoryNode registered_observers[MAX_OBSERVERS];
  memoryNode *first_observer[MAX_EVENTS];
  memoryNode *first_free;
  memoryNode *swap;
  EventPublisher *registered_publishers[MAX_EVENTS];

  public:
    void bind(const EventObserver& observer, const EventPublisher& publisher);
    void unbind(const EventObserver& observer, const EventPublisher& publisher);
    void clear();
    void update();

  private:
    memoryNode* find_observer (const EventObserver * observer, const int& event);
    int add_publisher (const EventPublisher& publisher);
    int find_publisher (const EventPublisher& publisher);

  // Singelton pattern
  public:
    static ObsPubManager& getInstance()
    {
        static ObsPubManager instance; // Guaranteed to be destroyed, Instantiated on first use.
        return instance;
    }

   private:
        ObsPubManager();
};

extern ObsPubManager& dwenguinoManager;
#endif
