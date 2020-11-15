#pragma once

#include "../module.hpp"
#include "../ship.hpp"

class Engine : public Module {
 private:
  double max_thrust;
  double max_power;

 public:
  Engine(std::string name, double hull, double max_thrust, double max_power);
  void simulate(double delta_time, Ship *ship);
};
