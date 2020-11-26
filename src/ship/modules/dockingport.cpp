#include "dockingport.hpp"

Dockingport::Dockingport(std::string name, double hull)
    : Module(name, "Dockingport", hull) {}

void Dockingport::simulate(Ship* ship, double delta_time) {
  this->can_dock = false;
  this->dockable_object = 0;
  if (!this->online) return;

  double sx;
  double sy;
  ship->getPos(sx, sy);

  // find dockable object
  auto gobjects = ship->getGameObjects();
  for (const auto& object : *gobjects) {
    // filter objects
    if (!object->isDockable()) continue;

    // calc distance
    double ox;
    double oy;
    object->getPos(ox, oy);

    ox -= sx;
    oy -= sy;
    double dist = sqrt(ox * ox + oy * oy);
    if (dist < 0.01) {
      // dockable
      this->can_dock = true;
      this->dockable_object = object;
      return;
    }
  }
}

bool Dockingport::dock() { return true; }
