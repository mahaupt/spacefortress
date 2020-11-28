#pragma once

#include "../module.hpp"
#include "../ship.hpp"

namespace module {
enum class WeaponType {};

class Weapon : public Module {
 public:
  Weapon(const std::string &name, const double &hull,
         const double &rate_of_fire, const double &output_vel,
         const double &shoot_energy);

  void simulate(double delta_time, Ship *ship);

 private:
  double rate_of_fire;
  double output_vel;
  double shoot_energy;

  bool autofire;
  bool active;
  double charge;
  double cooldown;
};
}  // namespace module