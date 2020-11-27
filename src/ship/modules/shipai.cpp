#include "shipai.hpp"

ShipAi::ShipAi(const std::string& name, double hull)
    : Module(name, "AI", hull), p_target(0) {}

void ShipAi::simulate(double delta_time, Ship* ship) {
  if (!this->online) return;

  if (this->p_target == 0) {
    this->findTarget(ship);
    return;
  }
  if (this->p_engine == 0) {
    this->findEngineModule(ship);
    return;
  }

  // get target coords and fly to it
  // get ship pos
  double sx;
  double sy;
  ship->getPos(sx, sy);

  // get target pos
  double tx;
  double ty;
  this->p_target->getPos(tx, ty);

  // vector to target
  double vttx = tx - sx;
  double vtty = ty - sy;
  double dist = sqrt(vttx * vttx + vtty * vtty);

  // too close - abort and search new target (only for test)
  if (dist <= 0.01) {
    this->p_target = 0;
    return;
  }

  // apply thrust
  p_engine->setThrust(vttx / dist, vtty / dist);

  // if in range and aggressive, shoot at it
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
    this->p_target = farthest_go;
  }
}

void ShipAi::findEngineModule(Ship* ship) {
  for (const auto& module : *(ship->getModules())) {
    if (module->getType() == "Engine") {
      this->p_engine = (Engine*)module;
      return;
    }
  }
}
