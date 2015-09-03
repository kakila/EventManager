/*
 * inputManager.cpp
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

#include "inputManager.h"

uint8_t button[] = {SW_N, SW_W, SW_S, SW_E, SW_C};

void inputManager::bind(const observer_t& observer, const event_t& ev)
{
  swap = first_free;             // Copy free ptr
  first_free = swap->nxt;        // move free ptr

  swap->obs = const_cast<observer_t *>(&observer);  // set obs in previously free ptr
  swap->nxt = first_observer[ev];                   // Point next to current first observer
  first_observer[ev] = swap;                        // Set current as first observer
}

void inputManager::unbind(const observer_t& observer, const event_t& ev)
{
  if (first_observer[ev] == nullptr)
    return;
  observer_t * ptr = const_cast<observer_t *>(&observer);
  if (ptr == first_observer[ev]->obs)
  {
    swap = first_observer[ev]->nxt; // copy first observer to nxt

    // move current first observer to first_free
    first_observer[ev]->nxt = first_free;
    first_observer[ev]->obs = nullptr;
    first_free = first_observer[ev];

    // set swap as first observer
    first_observer[ev] = swap;
  }
  else
  {
    // find the father of the node to unbind
    memoryNode *parent = find (ptr, ev);
    if (parent == nullptr)
      return;

    // Copy the node to unbind to swap and make the parent point to ther next node
    swap        = parent->nxt;
    parent->nxt = swap->nxt;

    // The node ot unbind as first_free
    swap->nxt  = first_free;
    swap->obs  = nullptr;
    first_free = swap;
  }
}

void inputManager::reset()
{
  for (size_t i =0; i<MAX_OBSERVERS-1; i++)
    registered_observers[i].nxt = (registered_observers + (i+1));
  first_free = &registered_observers[0];
  for (size_t i =0; i<MAX_EVENTS; i++)
    first_observer[i] = nullptr;
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
      while (node != nullptr)
      {
        node->obs->update(ev);
        node = node->nxt;
      }
    }
  }
}

memoryNode* inputManager::find(const observer_t * observer,  const event_t& ev)
{
  swap = first_observer[ev];
  while (swap->nxt != nullptr)
  {
    if (swap->nxt->obs == observer)
      return swap;
    swap = swap->nxt;
  }
  return nullptr;
}

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
