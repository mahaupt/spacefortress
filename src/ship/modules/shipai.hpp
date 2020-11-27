#pragma once
#include <cmath>

#include "../../gameobject.hpp"
#include "../../tools/vec2.hpp"
#include "../module.hpp"
#include "../ship.hpp"
#include "engine.hpp"

class ShipAi : public Module {
 public:
  ShipAi(const std::string& name, double hull);

  void simulate(double delta_time, Ship* ship);

 private:
  GameObject* p_target;
  Engine* p_engine;

  void findTarget(Ship* ship);
  void findEngineModule(Ship* ship);
};
