#pragma once

#include <vector>

#include "../../gameobject.hpp"
#include "../module.hpp"
#include "../ship.hpp"

class Sensor : public Module {
 public:
  Sensor(std::string name, double hull);

  void simulate(double delta_time, Ship *ship);
  std::vector<GameObject *> *getScannedObjects();

 private:
  Ship *ownship;
};
