/*
 * inputManager.h
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


#ifndef inputManager_h
#define inputManager_h

#ifndef ARDUINO_MAIN
#include "mock_dwenguino.h"
#endif

#ifndef MAX_OBS
#define MAX_OBSERVERS 10
#endif

#ifndef MAX_EVENTS
#define MAX_EVENTS 5
#endif

class Event
{
//  protected:
//    ~Event(){};

  const uint8_t type;

  public:
    Event(const uint8_t& t): type(t) {};
    const uint8_t& get_type() const {return type;};
};

// We do not want polymorphic destruction of these interfaces
// Protected destructors as in guideline #4
// http://www.gotw.ca/publications/mill18.htm
class Event_Publisher {
  protected:
    ~Event_Publisher() {};

  public:
    virtual bool is_triggered() = 0;
    virtual const Event &get_event() const = 0;
};

class IObserver {
  protected:
    ~IObserver() {}

  public:
    // pure virtual function providing interface framework.
    virtual void notify(const Event&) = 0;
};

class inputManager {
  struct memoryNode {
    IObserver *obs = nullptr;
    memoryNode *nxt = nullptr;
  };

  memoryNode registered_observers[MAX_OBSERVERS];
  memoryNode *first_observer[MAX_EVENTS];
  memoryNode *first_free;
  memoryNode *swap;
  Event_Publisher *registered_publishers[MAX_EVENTS];

  public:
    void bind(const IObserver& observer, const Event_Publisher& publisher);
    void unbind(const IObserver& observer, const Event_Publisher& publisher);
    void clear();
    void update();

  private:
    memoryNode* find_observer (const IObserver * observer, const int& event);
    int add_publisher (const Event_Publisher& publisher);
    int find_publisher (const Event_Publisher& publisher);

  // Singelton pattern
  public:
    static inputManager& getInstance()
    {
        static inputManager instance; // Guaranteed to be destroyed, Instantiated on first use.
        return instance;
    }

   private:
        inputManager();
};

#endif
