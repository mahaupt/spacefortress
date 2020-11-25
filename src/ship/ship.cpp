#include "ship.hpp"

Ship::Ship(std::string name, double hull) : modules(std::vector<Module *>()) {
  this->name = name;

  this->hull = hull;
  this->shield = 0;
  this->max_hull = hull;
  this->max_shield = 10;

  this->symbol = '@';
}

Ship::~Ship() {
  for (int i = 0; i < this->modules.size(); i++) {
    delete this->modules[i];
  }
}

void Ship::simulate(double delta_time) {
  GameObject::simulate(delta_time);
  for (int i = 0; i < this->modules.size(); i++) {
    this->modules[i]->simulate(delta_time, this);
  }
}

void Ship::addModule(Module *m) { this->modules.push_back(m); }

double Ship::getEnergy(double energy_needed) {
  double energy_drawn = 0;

  // search
  for (int i = 0; i < this->modules.size(); i++) {
    if (this->modules[i]->energy_available >= 0) {
      energy_drawn += this->modules[i]->getEnergy(energy_needed - energy_drawn);
      if (energy_drawn == energy_needed) {
        return energy_needed;
      }
    }
  }
  return energy_drawn;
}

double Ship::getEnergyLevel() {
  double total_energy_avbl = 0;

  for (int i = 0; i < this->modules.size(); i++) {
    if (this->modules[i]->type != GENERATOR) {
      total_energy_avbl += this->modules[i]->energy_available;
    }
  }

  return total_energy_avbl;
}

double Ship::getEnergyTotalCapacity() {
  double capacity = 0;

  for (int i = 0; i < this->modules.size(); i++) {
    if (this->modules[i]->max_capacity > 0) {
      capacity += this->modules[i]->max_capacity;
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
