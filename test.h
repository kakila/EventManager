#include "inputManager.h"

class Teller: public observer_t {
  size_t _id;
  public:
    Teller() { static int id = 0; _id = id++; }
    void update(const event_t& ev) {cout << "Observer " << _id << " catched event " << ev << endl;};
};
