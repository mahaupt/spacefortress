#include "module.hpp"

Module::Module(std::string name, std::string type, double hull)
    : online(true),
      name(name),
      type(type),
      hull(hull),
      max_hull(hull),
      max_capacity(0),
      energy_available(0),
      energy_needed(0) {}

double Module::getEnergy(double energy_needed) {
  if (energy_needed > this->energy_available) {
    double returned_energy = this->energy_available;
    this->energy_available = 0;

    return returned_energy;
  } else {
    this->energy_available -= energy_needed;

    return energy_needed;
  }
}
