#include "dockingport.hpp"

Dockingport::Dockingport(std::string name, double hull)
    : Module(name, "Dockingport", hull), ownship(0), docked(false) {}

void Dockingport::simulate(double delta_time, Ship* ship) {
  this->ownship = ship;

  // dont search docking partners when already docked
  // also keep dockable_object var
  if (this->docked) return;

  // Reset vars
  this->can_dock = false;
  this->dockable_object = 0;
  if (!this->online) return;

  // get ship position
  double sx;
  double sy;
  ship->getPos(sx, sy);

  // find dockable object in range
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

bool Dockingport::dock() {
  if (this->ownship == 0) return false;
  if (!this->can_dock) return false;
  if (this->dockable_object == 0) return false;

  // set game object to fixed
  this->ownship->setFixed(true);

  // sync positions
  double opx;
  double opy;
  this->dockable_object->getPos(opx, opy);
  this->ownship->setPos(opx, opy);

  this->docked = true;

  return true;
}

bool Dockingport::undock() {
  if (this->ownship == 0) return false;
  if (!this->docked) return false;

  this->ownship->setFixed(false);
  this->docked = false;

  return true;
}
