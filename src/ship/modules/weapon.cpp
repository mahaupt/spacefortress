#include "weapon.hpp"

using namespace module;

Weapon::Weapon(const std::string &name, const double &hull,
               const double &rate_of_fire, const double &output_vel,
               const double &max_power_input)
    : Module(name, "Weapon", hull),
      rate_of_fire(rate_of_fire),
      output_vel(output_vel),
      max_power_input(max_power_input) {}