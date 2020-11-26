#include "engine.hpp"

Engine::Engine(std::string name, double hull, double max_thrust,
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
  double fabs = sqrt(this->thr_cmd_x * this->thr_cmd_x +
                     this->thr_cmd_y * this->thr_cmd_y);

  // skip if fabs to small
  if (fabs == 0) return;

  // limit force vector to 1
  if (fabs > 1.0) {
    this->thr_cmd_x /= fabs;
    this->thr_cmd_y /= fabs;
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
  this->thr_cmd_x *= eng_thrust;
  this->thr_cmd_y *= eng_thrust;
  ship->applyForce(this->thr_cmd_x, this->thr_cmd_y);

  // reset thrust
  this->thr_cmd_x = 0;
  this->thr_cmd_y = 0;
}

/**
 * Sets engine thrust, must be a vector of magnitude 1
 * @param x Thrust in X direction
 * @param y Thrust in Y direction
 */
void Engine::setThrust(double x, double y) {
  this->thr_cmd_x = x;
  this->thr_cmd_y = y;
}
