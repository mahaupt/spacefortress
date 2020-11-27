#include "sensor.hpp"

Sensor::Sensor(const std::string &name, double hull)
    : Module(name, "Sensor", hull), ownship(0) {}

std::vector<GameObject *> *Sensor::getScannedObjects() {
  if (!this->online) return 0;
  if (this->ownship == 0) return 0;

  return this->ownship->getGameObjects();
}

void Sensor::simulate(double delta_time, Ship *ship) {
  if (!this->online) return;
  this->ownship = ship;

  // draw energy
  double e_need = 0.1 * 0.01 * delta_time;
  double e_got = ship->getEnergy(e_need);

  // turn off when not enough energy
  if (e_got < e_need) {
    this->online = false;
  }
}
