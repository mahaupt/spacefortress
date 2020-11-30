#include "sensor.hpp"

using namespace module;

Sensor::Sensor(const std::string &name, double hull)
    : Module(name, "Sensor", hull), ownship(nullptr) {}

/**
 * returns list of objects that are in sensor range, or nullpointer
 */
std::vector<std::shared_ptr<GameObject>> *Sensor::getScannedObjects() {
  if (!this->online) return nullptr;
  if (this->ownship == 0) return nullptr;

  return this->ownship->getGameObjects();
}

void Sensor::simulate(double delta_time, Ship *ship) {
  if (!this->online) {
    this->lock_progress = 0;
    this->plocked_object.reset();
    return;
  }
  this->ownship = ship;

  // draw energy
  double e_need = 0.1 * 0.01 * delta_time;
  double e_got = ship->getEnergy(e_need);

  // turn off when not enough energy
  if (e_got < e_need) {
    this->online = false;
    return;
  }

  // process target lock
  if (this->plocked_object.expired()) {
    this->lock_progress = 0;
  } else if (this->lock_progress < 1) {
    this->lock_progress += delta_time / 3.0;
    if (this->lock_progress > 1) {
      this->lock_progress = 1;
    }
  }

  // command to weapon to shoot?
}

// locking functions
void Sensor::startLock(const std::shared_ptr<GameObject> &go) {
  if (!this->online) return;
  this->plocked_object = go;
  this->lock_progress = 0;
}
void Sensor::clearLock() {
  this->plocked_object.reset();
  this->lock_progress = 0;
}
