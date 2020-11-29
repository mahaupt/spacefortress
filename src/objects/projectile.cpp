#include "projectile.hpp"

using namespace go;

Projectile::Projectile(std::vector<GameObject *> *pgobjects,
                       const std::string &name, GameObject *origin,
                       GameObject *target, double velocity)
    : GameObject(name, "Projectile", 0, 0),
      origin(origin),
      target(target),
      lifetime(60),
      pgobjects(pgobjects) {
  this->symbol = "\u2219";
  this->mass = 100;
  Vec2 spos = origin->getPos();
  this->setPos(spos);

  Vec2 vel =
      Vec2::getInterceptVel(spos, target->getPos(), target->getVel(), velocity);
  this->setVel(vel);
}

void Projectile::simulate(double delta_time) {
  GameObject::simulate(delta_time);

  // die
  this->lifetime -= delta_time;
  if (this->lifetime <= 0) {
    this->alive = false;
    return;
  }

  // go through object list and look for targets in close range
  // hit target
  Vec2 pos = this->getPos();
  for (const auto &object : *pgobjects) {
    if (object->getType() != "Projectile" && object != this->origin) {
      Vec2 toobj = object->getPos();
      toobj -= pos;

      // calc hit
      if (toobj.magnitude() < 0.002) {
        object->hit(this->mass * this->getVel().magnitude());
        this->alive = false;  // mark game object as dead
      }
    }
  }
}