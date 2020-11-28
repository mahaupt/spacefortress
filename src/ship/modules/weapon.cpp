#include "weapon.hpp"

using namespace module;

Weapon::Weapon(const std::string &name, const double &hull,
               const double &rate_of_fire, const double &output_vel,
               const double &shoot_energy)
    : Module(name, "Weapon", hull),
      rate_of_fire(rate_of_fire),
      output_vel(output_vel),
      shoot_energy(shoot_energy) {}

void Weapon::simulate(double delta_time, Ship *ship) {
  if (!this->online) return;
  if (this->cooldown > 0) {
    this->cooldown -= delta_time;
  }

  // check autofire
  if (this->autofire) {
    // check sensor info
  }

  // weapon set to active, charge and fire
  if (this->active) {
    double energy_needed = this->shoot_energy - this->charge;
    this->charge += ship->getEnergy(energy_needed);

    // enough energy?
    // cooldown completed? -> shoot
    if (this->charge >= this->shoot_energy && this->cooldown <= 0) {
      // create shell and apply energy
      // TODO

      // discharge
      this->charge -= this->shoot_energy;
      this->cooldown = 1.0 / this->rate_of_fire;
    }
  }
}