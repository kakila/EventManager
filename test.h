#include "inputManager.h"

class TestObserver: public observer_t {
  size_t _id;
  bool m_wasCalled = false;
  public:
    TestObserver();
    void update(const event_t& ev);
    bool wasCalled();
    void reset();
};

class TestInputManager : public inputManager {

};
