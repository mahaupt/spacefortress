#include "dockingport.hpp"

using namespace module;

Dockingport::Dockingport(const std::string& name, double hull)
    : Module(name, "Dockingport", hull), ownship(0), docked(false) {}

void Dockingport::simulate(double delta_time, Ship* ship) {
  this->ownship = ship;

  // dont search docking partners when already docked
  // also keep dockable_object var
  if (this->docked) return;

  // Reset vars
  this->can_dock = false;
  this->p_dockable_object.reset();
  if (!this->online) return;

  // get ship position
  Vec2 spos = ship->getPos();

  // find dockable object in range
  auto gobjects = ship->getGameObjects();
  for (const auto& object : *gobjects) {
    // filter objects
    if (!object->isDockable()) continue;
    if (object.get() == ship) continue;

    // calc distance
    Vec2 opos = object->getPosSafe();

    opos -= spos;

    if (opos.magnitude() < 0.01) {
      // dockable
      this->can_dock = true;
      this->p_dockable_object = object;
      return;
    }
  }
}

bool Dockingport::dock() {
  if (this->ownship == 0) return false;
  if (!this->can_dock) return false;

  // try to get game object
  auto go = this->p_dockable_object.lock();
  if (!go) return false;

  // set game object to fixed
  this->ownship->setFixed(true);

  // sync positions
  Vec2 pos = go->getPos();
  this->ownship->setPos(pos);

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
