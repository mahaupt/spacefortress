#include "shieldgenerator.hpp"

ShieldGenerator::ShieldGenerator(const std::string &name, double hull,
                                 double max_power_input,
                                 double max_shield_output)
    : Module(name, "ShieldGenerator", hull),
      max_power_input(max_power_input),
      max_shield_output(max_shield_output) {}

void ShieldGenerator::simulate(double delta_time, Ship *ship) {
  if (!this->online) {
    return;
  }

  double free_shield = ship->getMaxShield() - ship->getShield();
  if (free_shield <= 0) {
    return;
  }

  // limit shield generation to max shield capacity
  double power_input = this->max_power_input * delta_time;
  double shield_output = this->max_shield_output * delta_time;
  if (shield_output > free_shield) {
    double x = free_shield / shield_output;
    shield_output *= x;
    power_input *= x;
  }

  // limit shield generation to power available
  double actual_power_input = ship->getEnergy(power_input);
  if (actual_power_input < power_input) {
    double x = actual_power_input / power_input;
    shield_output *= x;
  }

  ship->addShield(shield_output);
}
