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
  Vec2 spos = ship->getPos();

  // get target pos
  Vec2 tpos = this->p_target->getPos();

  // vector to target
  Vec2 vtgt = tpos - spos;
  double dist = vtgt.magnitude();

  // too close - abort and search new target (only for test)
  if (dist <= 0.01) {
    this->p_target = 0;
    return;
  }

  // apply thrust
  p_engine->setThrust(vtgt / dist);

  // if in range and aggressive, shoot at it
}

/**
 * finds target for the AI to steer to
 * @param ship ai owned ship
 */
void ShipAi::findTarget(Ship* ship) {
  // get ship pos
  Vec2 spos = ship->getPos();

  // if hostile, find enemy ship
  // if friendly, find market opportunity

  // test : find farthest planet
  double farthest_dist = 0;
  GameObject* farthest_go = 0;

  for (const auto& object : *(ship->getGameObjects())) {
    if (object->getType() == "Planet") {
      Vec2 opos = object->getPos();
      opos -= spos;
      double dist = opos.magnitude();

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
