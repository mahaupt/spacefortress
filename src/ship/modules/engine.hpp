#pragma once

#include <cmath>

#include "../../tools/vec2.hpp"
#include "../module.hpp"
#include "../ship.hpp"

namespace module {
class Engine : public Module {
 public:
  Engine(const std::string &name, double hull, double max_thrust,
         double max_power);
  void simulate(double delta_time, Ship *ship);

  void setThrust(const Vec2 &thr);

 private:
  double max_thrust;
  double max_power;

  Vec2 thr_cmd;
};
}  // namespace module