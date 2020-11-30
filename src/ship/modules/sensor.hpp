#pragma once

#include <memory>
#include <vector>

#include "../../gameobject.hpp"
#include "../module.hpp"
#include "../ship.hpp"

namespace module {
class Sensor : public Module {
 public:
  Sensor(const std::string &name, double hull);

  void simulate(double delta_time, Ship *ship);
  std::vector<std::shared_ptr<GameObject>> *getScannedObjects();

  // locking targets
  void startLock(const std::shared_ptr<GameObject> &go);
  void clearLock();
  std::weak_ptr<GameObject> getLockTarget() { return plocked_object; }
  double getLockProgress() { return this->lock_progress; }

 private:
  Ship *ownship;

  std::weak_ptr<GameObject> plocked_object;
  double lock_progress;
};
}  // namespace module
