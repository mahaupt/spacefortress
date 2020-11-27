#pragma once

#include <cmath>

#include "../module.hpp"
#include "../ship.hpp"

class Engine : public Module {
 public:
  Engine(const std::string &name, double hull, double max_thrust,
         double max_power);
  void simulate(double delta_time, Ship *ship);

  void setThrust(double x, double y);

 private:
  double max_thrust;
  double max_power;

  double thr_cmd_x;
  double thr_cmd_y;
};
