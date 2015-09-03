#include "inputManager.h"

int main()
{
  inputManager& buttonManager = inputManager::getInstance();

  observer_t Obs0, Obs1;
  buttonManager.bind(Obs0, event_t::N);
  buttonManager.bind(Obs0, event_t::S);

  buttonManager.bind(Obs1, event_t::W);
  buttonManager.bind(Obs1, event_t::S);
  buttonManager.bind(Obs1, event_t::C);

  buttonManager.bind(Obs0, event_t::W);

  buttonManager.notify();

  buttonManager.clear();
  buttonManager.bind(Obs0, event_t::N);
  buttonManager.bind(Obs0, event_t::W);
  buttonManager.bind(Obs1, event_t::N);
  buttonManager.bind(Obs1, event_t::W);

  buttonManager.notify();

  return 0;
}
