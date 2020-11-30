#pragma once

#include <cmath>
#include <memory>
#include <vector>

#include "../../gameobject.hpp"
#include "../../tools/log.hpp"
#include "../module.hpp"
#include "../ship.hpp"

namespace module {
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
  std::weak_ptr<GameObject> p_dockable_object;
};
}  // namespace module
