#pragma once
#include <string>

class Ship;

class Module {
 public:
  Module(std::string name, std::string type, double hull);
  virtual ~Module() {}

  // info funcitons
  std::string getType() { return this->type; }
  double getEnergyAvbl() { return this->energy_available; }

  // manipulation
  virtual void simulate(double delta_time, Ship *ship){};
  double getEnergy(double energy_needed);

 protected:
  bool online;
  std::string name;
  std::string type;

  double hull;
  double max_hull;

  double energy_available;
  double energy_needed;
};
