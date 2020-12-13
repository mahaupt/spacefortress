#include "ship.hpp"

Ship::Ship(const std::string &name, double hull,
           std::vector<std::shared_ptr<GameObject>> *ptr_gobjects)
    : GameObject(name, "Ship", 0, 0), ptr_gobjects(ptr_gobjects) {
  this->hull = hull;
  this->shield = 0;
  this->max_hull = hull;
  this->max_shield = 10;

  this->symbol = L'\u2206';
}

Ship::~Ship() {
  for (const auto &module : this->modules) {
    delete module;
  }
  this->modules.clear();
}

void Ship::addStandardModules() {
  this->addModule(new module::Generator("Generator MK I", 1, 1));
  this->addModule(new module::Lifesupport("LifeSupport", 1, 3));
  this->addModule(new module::Dockingport("Docking port", 1));
  this->addModule(new module::Sensor("SR Sensor 2.7", 1));
  this->addModule(new module::Cargo("Cargo hold", 1, 1000));
  this->addModule(
      new module::ShieldGenerator("Shield Generator MK I", 1, 0.5, 1));
  this->addModule(new module::Engine("Engine MK I", 1, 1, 2));
  this->addModule(new module::Weapon("S Projectile", 1, 0.5, 0.1, 1));
  this->addModule(new module::Capacitor("Capacitor MK I", 1, 100, 1, 10));
}

void Ship::simulate(double delta_time) {
  {
    std::lock_guard<std::mutex> lock_guard(this->mx_object);
    for (const auto &module : this->modules) {
      module->simulate(delta_time, this);
    }
  }

  // simulate game object moving
  GameObject::simulate(delta_time);
}

void Ship::addModule(Module *m) { this->modules.push_back(m); }

/**
 * Draws energy fom energy providing modules (Generator, Capacitor)
 * @param  energy_needed the amount of energy needed
 * @return               the amount of energy available and removed
 */
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

/**
 * Calculates current energy level
 * @return double Energy
 */
double Ship::getEnergyLevel() {
  double total_energy_avbl = 0;

  for (const auto &module : this->modules) {
    if (module->getType() != "Generator") {
      total_energy_avbl += module->getEnergyAvbl();
    }
  }

  return total_energy_avbl;
}

/**
 * calculates total energy capacity of ship
 * @return Energy Capacity
 */
double Ship::getEnergyTotalCapacity() {
  double capacity = 0;

  for (const auto &module : this->modules) {
    if (module->getType() == "Capacitor") {
      capacity += ((module::Capacitor *)module)->getMaxCapacity();
    }
  }

  return capacity;
}

/**
 * adds a shield amount to the ship
 * called from shield generator
 * @param shield Amount of shield
 */
void Ship::addShield(double shield) {
  this->shield += shield;

  if (this->shield > this->max_shield) {
    this->shield = this->max_shield;
  }
}

/**
 * Returns pointer first online module with given module type
 * @param  type Type of module
 * @return      Module pointer
 */
Module *Ship::getFirstModule(const std::string &type) {
  for (const auto &module : this->modules) {
    if (module->isOnline() && module->getType() == type) {
      return module;
    }
  }
  return nullptr;
}

/**
 * Damage calculating function. Called from outside!
 * @param energy impact energy of projectile
 */
void Ship::hit(double energy) {
  std::lock_guard<std::mutex> lock_guard(this->mx_object);

  // shield
  double e = energy;
  e -= this->shield;
  this->shield -= energy;
  if (e < 0) e = 0;

  // hull
  this->hull -= e;

  // modules

  // destroy ship:
  if (this->hull <= 0) {
    this->alive = false;
  }
}
