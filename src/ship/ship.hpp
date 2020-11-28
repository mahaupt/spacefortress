#pragma once
#include <curses.h>

#include <string>
#include <vector>

#include "../gameobject.hpp"
#include "module.hpp"
#include "modules/capacitor.hpp"

class Ship : public GameObject {
 public:
  Ship(const std::string &name, double hull,
       std::vector<GameObject *> *ptr_gobjects);
  ~Ship();

  // info functions
  double getHull() { return this->hull; }
  double getMaxHull() { return this->max_hull; }
  double getShield() { return this->shield; }
  double getMaxShield() { return this->max_shield; }
  size_t getModuleCount() { return this->modules.size(); }
  double getEnergyLevel();
  double getEnergyTotalCapacity();
  std::vector<GameObject *> *getGameObjects() { return this->ptr_gobjects; }
  std::vector<Module *> *getModules() { return &(this->modules); }
  bool isDocked() { return this->is_fixed; }
  Module *getFirstModule(const std::string &type);

  // management functions
  void simulate(double delta_time);
  void addModule(Module *m);

  // module functions
  double getEnergy(double energy_needed);
  void addShield(double shield);

 private:
  double hull;
  double shield;
  double max_hull;
  double max_shield;

  std::vector<Module *> modules;
  std::vector<GameObject *> *ptr_gobjects;
};
