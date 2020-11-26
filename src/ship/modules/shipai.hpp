#pragma once
#include <cmath>

#include "../../gameobject.hpp"
#include "../module.hpp"
#include "../ship.hpp"

class ShipAi : public Module {
 public:
  ShipAi(std::string name, double hull);

  void simulate(double delta_time, Ship* ship);

 private:
  GameObject* target;

  void findTarget(Ship* ship);
};
