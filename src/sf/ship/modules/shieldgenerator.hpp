#pragma once

#include "../module.hpp"
#include "../ship.hpp"

namespace module {
class ShieldGenerator : public Module {
 private:
  double max_power_input;
  double max_shield_output;

 public:
  ShieldGenerator(const std::string& name, double hull, double max_power_input,
                  double max_shield_output);
  void simulate(double delta_time, Ship* ship);
};
}  // namespace module