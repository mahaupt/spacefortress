#include "capacitor.hpp"

Capacitor::Capacitor(std::string name, double hull, double max_capacity,
                     double max_power_input, double max_power_output)
    : Module(name, "Capacitor", hull),
      energy(0),
      max_power_input(max_power_input),
      max_power_output(max_power_output) {
  this->max_capacity = max_capacity;
}

void Capacitor::simulate(double delta_time, Ship *ship) {
  if (!this->online) {
    return;
  }

  double free_cap_space = max_capacity - energy_available;
  double energy_intake_limit = max_power_input * delta_time;
  double energy_drawn = std::min(free_cap_space, energy_intake_limit);

  energy_available += ship->getEnergy(energy_drawn);
}
