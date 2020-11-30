#pragma once

#include <memory>

#include "../../objects/projectile.hpp"
#include "../module.hpp"
#include "../ship.hpp"
#include "sensor.hpp"

namespace module {
enum class WeaponType {};

class Weapon : public Module {
 public:
  Weapon(const std::string &name, const double &hull,
         const double &rate_of_fire, const double &output_vel,
         const double &shoot_energy);

  void simulate(double delta_time, Ship *ship);

  void setAutofire(const bool &a) { this->autofire = a; }
  bool getAutofire() { return this->autofire; }
  void setActive(const bool &a) { this->active = a; }
  bool getActive() { return this->active; }
  double getCharge() { return this->charge / this->shoot_energy; }

 private:
  double rate_of_fire;
  double output_vel;
  double shoot_energy;

  bool autofire;
  bool active;
  double charge;
  double cooldown;

  Sensor *psensor;
};
}  // namespace module
