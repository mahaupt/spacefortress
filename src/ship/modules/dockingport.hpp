#pragma once

#include <cmath>
#include <vector>

#include "../../gameobject.hpp"
#include "../../tools/log.hpp"
#include "../module.hpp"
#include "../ship.hpp"

class Dockingport : public Module {
 public:
  Dockingport(const std::string& name, double hull);
  void simulate(double delta_time, Ship* ship);

  bool canDock() { return this->can_dock; }
  bool dock();
  bool undock();

 private:
  Ship* ownship;
  bool docked;
  bool can_dock;
  GameObject* dockable_object;
};
