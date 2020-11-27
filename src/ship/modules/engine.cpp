#include "engine.hpp"

Engine::Engine(const std::string &name, double hull, double max_thrust,
               double max_power)
    : Module(name, "Engine", hull),
      max_thrust(max_thrust),
      max_power(max_power) {}

/**
 * This simulation method reads the force x and y values from the game
 * GameObject Its interpreted as a 2D vector with a length between 1 and 0
 * representing 100% to 0% power It draws energy from the ship and rewrites the
 * force vectors to the actual force
 */
void Engine::simulate(double delta_time, Ship *ship) {
  if (!this->online) return;

  // take thrust command
  double fabs = this->thr_cmd.magnitude();

  // skip if fabs to small
  if (fabs == 0) return;

  // limit force vector to 1
  if (fabs > 1.0) {
    this->thr_cmd.normalize();
    fabs = 1.0;
  }

  // get engine thrust power
  double eng_thrust = this->max_thrust * fabs;
  double eng_power = this->max_power * fabs * delta_time;

  // try to get engine power
  double drawn_power = ship->getEnergy(eng_power);
  if (drawn_power == 0) return;  // no energy for thrust avbl
  if (drawn_power < eng_power) {
    // not enough energy avbl - limit thrust
    eng_thrust *= drawn_power / eng_power;
  }

  // apply thrust
  this->thr_cmd *= eng_thrust;
  ship->addForce(this->thr_cmd);

  // reset thrust
  this->thr_cmd.zero();
}

/**
 * Sets engine thrust, must be a vector of magnitude 1 or less
 * @param thr Vec2 Thrust Command
 */
void Engine::setThrust(const Vec2 &thr) { this->thr_cmd = thr; }
