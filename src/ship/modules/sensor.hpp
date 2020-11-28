#pragma once

#include <vector>

#include "../../gameobject.hpp"
#include "../module.hpp"
#include "../ship.hpp"

namespace module {
class Sensor : public Module {
 public:
  Sensor(const std::string &name, double hull);

  void simulate(double delta_time, Ship *ship);
  std::vector<GameObject *> *getScannedObjects();

  // locking targets
  void startLock(GameObject *go);
  void clearLock();
  GameObject *getLockTarget() { return this->plocked_object; }
  double getLockProgress() { return this->lock_progress; }

 private:
  Ship *ownship;

  GameObject *plocked_object;
  double lock_progress;
};
}  // namespace module