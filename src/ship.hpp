#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "module.hpp"

class Ship {
 private:
  std::string name;

  double hull;
  double shield;
  double max_hull;
  double max_shield;

  std::vector<Module *> modules;

 public:
  Ship(std::string name, double hull);
  ~Ship();

  // management functions
  void info();
  void simulate(double delta_time);
  void addModule(Module *m);

  // module functions
  double getEnergy(double energy_needed);
  double getEnergyLevel();
  double getEnergyTotalCapacity();
  double getShieldCapacity() { return this->max_shield; }
  double getShieldLevel() { return this->shield; }
  void addShield(double shield);
};
