/*
 * CallbckPubManager.cpp
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

#include "EventManager.h"

CallbckPubManager::CallbckPubManager() {
  for (size_t i =0; i<MAX_OBSERVERS-1; i++)
    registered_observers[i].nxt = (registered_observers + (i+1));
  first_free = &registered_observers[0];

  for (size_t i =0; i<MAX_EVENTS; i++)
    registered_publishers[i] = nullptr;
};

void CallbckPubManager::bind(const Callback & observer, const EventPublisher& publisher)
{
  int ev = add_publisher(publisher);
  if (ev == -1) // Couldn't add
    return;

  swap = first_free;             // Copy free ptr
  first_free = swap->nxt;        // move free ptr

  swap->obs = observer;  // set obs in previously free ptr
  swap->nxt = first_observer[ev];                   // Point next to current first observer
  first_observer[ev] = swap;                        // Set current as first observer
}

void CallbckPubManager::unbind(const Callback & observer, const EventPublisher& publisher)
{
  int ev = find_publisher(publisher);
  if (ev == -1 || first_observer[ev] == nullptr)
    return;
  Callback  ptr = observer;
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
    memoryNode *parent = find_observer (ptr, ev);
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

void CallbckPubManager::clear()
{
  for (size_t i =0; i<MAX_OBSERVERS-1; i++)
    registered_observers[i].nxt = (registered_observers + (i+1));
  first_free = &registered_observers[0];
  for (size_t i =0; i<MAX_EVENTS; i++)
    first_observer[i] = nullptr;
}

void CallbckPubManager::update()
{
  memoryNode *node;
  for (unsigned int i=0; i<MAX_EVENTS; i++)
  {
    if (registered_publishers[i] == nullptr)
      continue;
    if (registered_publishers[i]->is_triggered())
    {
      const Event *new_event = registered_publishers[i]->get_event();
      node = first_observer[i];
      while (node != nullptr)
      {
        node->obs(new_event);
        node = node->nxt;
      }
    }
  }
}

CallbckPubManager::memoryNode* CallbckPubManager::find_observer(const Callback  & observer,  const int & ev)
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

int CallbckPubManager::add_publisher (const EventPublisher& publisher)
{
  for (size_t i =0; i<MAX_EVENTS; i++)
  {
       if (registered_publishers[i] == nullptr || registered_publishers[i] == &publisher)
       {
          registered_publishers[i] = const_cast<EventPublisher *>(&publisher);
          return i;
       }
  }
  return -1;
}

int CallbckPubManager::find_publisher (const EventPublisher& publisher)
{
  for (size_t i =0; i<MAX_EVENTS; i++)
  {
       if (registered_publishers[i] == &publisher)
          return i;
  }
  return -1;
}

CallbckPubManager& dwenguinoManager = CallbckPubManager::getInstance();
