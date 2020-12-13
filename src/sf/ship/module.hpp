#pragma once
#include <string>

class Ship;

/**
 * base class to define modules for the ship
 * todo: adjust class to fit for general gameobjects. Maybe adding modules to space creatures / stations
 */
class Module {
 public:
  Module(const std::string &name, const std::string &type, double hull);
  virtual ~Module() {}

  // info funcitons
  bool isOnline() { return this->online; }
  void setOnline(bool o) { this->online = o; }
  std::string getName() { return this->name; }
  std::string getType() { return this->type; }
  double getEnergyAvbl() { return this->energy_available; }

  // manipulation
  virtual void simulate(double delta_time, Ship *ship){};
  virtual double getEnergy(double energy_needed);

 protected:
  bool online;
  std::string name;
  std::string type;

  double hull;
  double max_hull;

  double energy_available;
  double energy_needed;
};
