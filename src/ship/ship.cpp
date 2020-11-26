#include "ship.hpp"

Ship::Ship(std::string name, double hull,
           std::vector<GameObject *> *ptr_gobjects)
    : ptr_gobjects(ptr_gobjects) {
  this->name = name;

  this->hull = hull;
  this->shield = 0;
  this->max_hull = hull;
  this->max_shield = 10;

  this->symbol = "\u2206";
}

Ship::~Ship() {
  for (const auto &module : this->modules) {
    delete module;
  }
  this->modules.clear();
}

void Ship::simulate(double delta_time) {
  for (const auto &module : this->modules) {
    module->simulate(delta_time, this);
  }

  // simulate game object moving
  GameObject::simulate(delta_time);
}

void Ship::addModule(Module *m) { this->modules.push_back(m); }

double Ship::getEnergy(double energy_needed) {
  double energy_drawn = 0;

  // search
  for (const auto &module : this->modules) {
    if (module->getEnergyAvbl() >= 0) {
      energy_drawn += module->getEnergy(energy_needed - energy_drawn);
      if (energy_drawn == energy_needed) {
        return energy_needed;
      }
    }
  }
  return energy_drawn;
}

double Ship::getEnergyLevel() {
  double total_energy_avbl = 0;

  for (const auto &module : this->modules) {
    if (module->getType() != "Generator") {
      total_energy_avbl += module->getEnergyAvbl();
    }
  }

  return total_energy_avbl;
}

double Ship::getEnergyTotalCapacity() {
  double capacity = 0;

  for (const auto &module : this->modules) {
    if (module->getMaxCapacity() > 0) {
      capacity += module->getMaxCapacity();
    }
  }

  return capacity;
}

void Ship::addShield(double shield) {
  this->shield += shield;

  if (this->shield > this->max_shield) {
    this->shield = this->max_shield;
  }
}
