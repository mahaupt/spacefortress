#pragma once

#include "../module.hpp"

namespace module {
enum class WeaponType {};

class Weapon : public Module {
 public:
  Weapon(const std::string &name, const double &hull,
         const double &rate_of_fire, const double &output_vel,
         const double &max_power_input);

 private:
  double rate_of_fire;
  double output_vel;
  double max_power_input;
};
}  // namespace module