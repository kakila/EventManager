/*
 * test.cpp
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

#include "inputManager.h"

class Teller: public object_t {
  size_t _id;
  public:
    Teller() { static int id = 0; _id = id++; }
    void update(const event_t& ev) {cout << "Observer " << _id << " catched event " << ev << endl;};
};

int main()
{
  inputManager& buttonManager = inputManager::getInstance();

  Teller Obs0, Obs1;

  cout << "First load" << endl;
  buttonManager.bind(Obs0, event_t::N);
  buttonManager.bind(Obs0, event_t::S);

  buttonManager.bind(Obs1, event_t::W);
  buttonManager.bind(Obs1, event_t::S);
  buttonManager.bind(Obs1, event_t::C);

  buttonManager.bind(Obs0, event_t::W);

  buttonManager.notify();

  cout << endl;
  cout << "Reset and reload" << endl;
  buttonManager.reset();

  buttonManager.bind(Obs0, event_t::N);
  buttonManager.bind(Obs0, event_t::W);
  buttonManager.bind(Obs1, event_t::N);
  buttonManager.bind(Obs1, event_t::W);

  buttonManager.notify();

  cout << endl;
  cout << "Unbind" << endl;
  buttonManager.unbind(Obs0, event_t::N); buttonManager.unbind(Obs0, event_t::N);
  buttonManager.unbind(Obs0, event_t::W);
  buttonManager.unbind(Obs1, event_t::N);

  buttonManager.notify();

  cout << endl;
  cout << "Reconfigure" << endl;
  buttonManager.bind(Obs0, event_t::W);
  buttonManager.bind(Obs0, event_t::E);
  buttonManager.bind(Obs1, event_t::S);

  buttonManager.notify();

  return 0;
}
