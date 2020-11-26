#include "shipai.hpp"

ShipAi::ShipAi(std::string name, double hull)
    : Module(name, "AI", hull), target(0) {}

void ShipAi::simulate(double delta_time, Ship* ship) {
  if (!this->online) return;

  if (this->target == 0) {
    this->findTarget(ship);
  } else {
    // get target coords and fly to it

    // if in range and aggressive, shoot at it
  }
}

/**
 * finds target for the AI to steer to
 * @param ship ai owned ship
 */
void ShipAi::findTarget(Ship* ship) {
  // get ship pos
  double sx;
  double sy;
  ship->getPos(sx, sy);

  // if hostile, find enemy ship
  // if friendly, find market opportunity

  // test : find farthest planet
  double farthest_dist = 0;
  GameObject* farthest_go = 0;

  for (const auto& object : *(ship->getGameObjects())) {
    if (object->getType() == "Planet") {
      double gx;
      double gy;
      object->getPos(gx, gy);
      gx -= sx;
      gy -= sy;
      double dist = sqrt(gx * gx + gy * gy);

      if (dist > farthest_dist) {
        farthest_dist = dist;
        farthest_go = object;
      }
    }
  }

  // pick farthest object
  if (farthest_go != 0) {
    this->target = farthest_go;
  }
}
