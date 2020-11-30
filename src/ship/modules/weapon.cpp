#include "weapon.hpp"

using namespace module;

Weapon::Weapon(const std::string &name, const double &hull,
               const double &rate_of_fire, const double &output_vel,
               const double &shoot_energy)
    : Module(name, "Weapon", hull),
      rate_of_fire(rate_of_fire),
      output_vel(output_vel),
      shoot_energy(shoot_energy),
      autofire(false),
      active(false),
      charge(0),
      cooldown(0),
      psensor(nullptr) {}

void Weapon::simulate(double delta_time, Ship *ship) {
  if (!this->online) return;
  if (this->cooldown > 0) {
    this->cooldown -= delta_time;
  }
  if (this->psensor == nullptr)
    this->psensor = (Sensor *)ship->getFirstModule("Sensor");

  // check target
  std::shared_ptr<GameObject> tgt;
  if (this->psensor != nullptr) {
    if (this->psensor->getLockProgress() >= 1) {
      tgt = this->psensor->getLockTarget().lock();
    }
  }

  // check autofire
  if (this->autofire) {
    // check sensor info
    this->active = true;
  }

  // weapon set to active, charge and fire
  if (this->active) {
    double energy_needed = this->shoot_energy - this->charge;
    this->charge += ship->getEnergy(energy_needed);

    // enough energy?
    // cooldown completed? -> shoot
    if (this->charge >= this->shoot_energy && this->cooldown <= 0 && tgt) {
      // create shell and apply energy
      auto gobjects = ship->getGameObjects();
      gobjects->push_back(std::make_shared<go::Projectile>(
          ship->getGameObjects(), "Ballistic", ship, tgt, this->output_vel));

      // discharge
      this->charge -= this->shoot_energy;
      this->cooldown = 1.0 / this->rate_of_fire;
      this->active = false;
    }
  }

  // slowly discharge
  this->charge -= this->charge * 0.01 * delta_time;
}
