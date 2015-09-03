#include "inputManager.h"

uint8_t button[] = {SW_N, SW_W, SW_S, SW_E, SW_C};

void inputManager::bind(const observer_t& observer, const event_t& ev)
{
  observer_t *ptr = const_cast<observer_t *>(&observer);

  size_t idx = find(ptr);
  if (idx > end) // Add only if not found
  {
    registered_observers[end].obs     = ptr;
    registered_observers[end].nxt[ev] = first_observer[ev];
    first_observer[ev]                = &registered_observers[end];
    end++;
  }
  else // re-wire
  {
    registered_observers[idx].nxt[ev] = first_observer[ev];
    first_observer[ev]                = &registered_observers[idx];
  }
}

void inputManager::clear()
{
  end = 0;
  for (size_t i=0; i < MAX_EVENTS; i++)
  {
    first_observer[i] = NULL;
    for (size_t j=0; j < MAX_OBSERVERS; j++)
      {
        registered_observers[j].obs    = NULL;
        registered_observers[j].nxt[i] = NULL;
      }
  }
}

void inputManager::notify()
{
  event_t ev;
  memoryNode *node;
  for (unsigned int i=0; i<MAX_EVENTS; i++)
  {
   // Check for onpress events
    if (digitalRead(button[i]) == PRESSED)
    {
      // FIXME: how to do this?
      switch (button[i])
      {
        case SW_N: ev  = N; break;
        case SW_W: ev  = W; break;
        case SW_S: ev  = S; break;
        case SW_E: ev  = E; break;
        case SW_C: ev  = C; break;
      }

      node = first_observer[ev];
      while (node != NULL)
      {
        node->obs->update(ev);
        node = node->nxt[ev];
      }
    }
  }
}

size_t inputManager::find(const observer_t* observer)
{
  size_t i = 0;
  while (registered_observers[i].obs != observer)
      if (++i > end)
        break;
  return i;
}

/// TO ERASE
uint8_t digitalRead (unsigned int port)
{
//  if (port == SW_S)
    return 1;
//  return 0;
};

ostream& operator<<(ostream& os, const event_t& ev)
{
    switch(ev)
    {
        case N: os << "N"; break;
        case W: os << "W"; break;
        case S: os << "S"; break;
        case E: os << "E"; break;
        case C: os << "C"; break;
        default : os.setstate(ios_base::failbit);
    }
    return os;
}
