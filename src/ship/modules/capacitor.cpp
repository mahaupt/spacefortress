#include "capacitor.hpp"

using namespace module;

Capacitor::Capacitor(const std::string &name, double hull, double max_capacity,
                     double max_power_input, double max_power_output)
    : Module(name, "Capacitor", hull),
      max_power_input(max_power_input),
      max_power_output(max_power_output),
      max_capacity(max_capacity),
      power_output_avbl(0) {}

void Capacitor::simulate(double delta_time, Ship *ship) {
  if (!this->online) {
    return;
  }

  // load capacitor
  double free_cap_space = max_capacity - energy_available;
  double energy_intake_limit = max_power_input * delta_time;
  double energy_drawn = std::min(free_cap_space, energy_intake_limit);

  energy_available += ship->getEnergy(energy_drawn);

  // reset power output limit
  this->power_output_avbl = this->max_power_output * delta_time;
}

double Capacitor::getEnergy(double energy_needed) {
  if (this->power_output_avbl <= 0) {
    return 0;
  } else if (energy_needed > this->power_output_avbl) {
    double eng_avbl = this->power_output_avbl;
    this->power_output_avbl = 0;
    return Module::getEnergy(eng_avbl);
  } else {
    this->power_output_avbl -= energy_needed;
    return Module::getEnergy(energy_needed);
  }
}
