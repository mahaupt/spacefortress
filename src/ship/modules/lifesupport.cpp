#include "lifesupport.hpp"

Lifesupport::Lifesupport(const std::string& name, double hull, double capacity)
    : Module(name, "Lifesupport", hull), capacity(capacity) {}

void Lifesupport::simulate(double delta_time, Ship* ship) {
  if (!this->online) return;

  double e_need = 0.1 * capacity * delta_time;
  double e_got = ship->getEnergy(e_need);

  if (e_got < e_need) {
    this->online = false;
  }
}
