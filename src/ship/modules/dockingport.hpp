#pragma once

#include <cmath>
#include <vector>

#include "../../gameobject.hpp"
#include "../module.hpp"
#include "../ship.hpp"

class Dockingport : public Module {
 public:
  Dockingport(std::string name, double hull);
  void simulate(Ship* ship, double delta_time);

  bool canDock() { return this->can_dock; }
  bool dock();

 private:
  bool can_dock;
  GameObject* dockable_object;
};
