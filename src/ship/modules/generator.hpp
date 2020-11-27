#pragma once
#include "../module.hpp"
#include "../ship.hpp"

class Generator : public Module {
 private:
  double max_power_output;
  double last_power_usage;  // usage last tick
  double last_power_generation;

 public:
  Generator(const std::string& name, double hull, double power_output);
  void simulate(double delta_time, Ship* ship);
};
