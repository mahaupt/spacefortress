#include "generator.hpp"

Generator::Generator(std::string name, double hull, double power_output)
    : Module(name, hull, GENERATOR), max_power_output(power_output) {}

void Generator::simulate(double delta_time, Ship* ship) {
  this->energy_available = 0;
  if (!this->online) {
    return;
  }

  // try to add max power
  this->energy_available = max_power_output * delta_time;
}
