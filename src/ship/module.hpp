#pragma once
#include <string>

class Ship;

enum ModuleType {
  ACTIVE,    // active energy drawing module
  PASSIVE,   // passive module - no energy needed
  GENERATOR  // generator - generates energy
};

class Module {
 public:
  bool online;
  std::string name;
  ModuleType type;

  double hull;
  double max_hull;

  double max_capacity;
  double energy_available;
  double energy_needed;

  Module(std::string name, double hull, ModuleType type);
  virtual ~Module() {}
  virtual void simulate(double delta_time, Ship *ship){};

  double getEnergy(double energy_needed);
};
