#pragma once
#include <curses.h>

#include <string>
#include <vector>

#include "module.hpp"

class Ship {
 public:
  Ship(std::string name, double hull);
  ~Ship();

  // info functions
  std::string getName() { return this->name; }
  double getHull() { return this->hull; }
  double getMaxHull() { return this->max_hull; }
  double getShield() { return this->shield; }
  double getMaxShield() { return this->max_shield; }
  size_t getModuleCount() { return this->modules.size(); }
  double getEnergyLevel();
  double getEnergyTotalCapacity();

  // management functions
  void simulate(double delta_time);
  void addModule(Module *m);

  // module functions
  double getEnergy(double energy_needed);
  void addShield(double shield);

 private:
  std::string name;

  double hull;
  double shield;
  double max_hull;
  double max_shield;

  std::vector<Module *> modules;
};
