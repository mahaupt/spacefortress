#include "projectile.hpp"

using namespace go;

Projectile::Projectile(std::vector<std::shared_ptr<GameObject>> *pgobjects,
                       const std::string &name, GameObject *origin,
                       const std::shared_ptr<GameObject> &target,
                       double velocity)
    : GameObject(name, "Projectile", 0, 0),
      origin(origin),
      target(target),
      lifetime(60),
      pgobjects(pgobjects) {
  this->symbol = L'\u2219';
  this->mass = 100;
  Vec2 spos = origin->getPos();
  this->setPos(spos);

  Vec2 vel =
      Vec2::getInterceptVel(spos, target->getPos(), target->getVel(), velocity);
  this->setVel(vel);
}

void Projectile::simulate(double delta_time) {
  GameObject::simulate(delta_time);
  std::lock_guard<std::mutex> lock_guard(this->mx_object);

  // die
  this->lifetime -= delta_time;
  if (this->lifetime <= 0) {
    this->alive = false;
    return;
  }

  // go through object list and look for targets in close range
  // hit target
  for (const auto &object : *pgobjects) {
    // if (object.get() == this) continue; // redundant
    if (object->getType() != "Projectile" && object.get() != origin) {
      Vec2 toobj = object->getPosSafe();
      toobj -= this->pos;

      // calc hit
      if (toobj.magnitude() < 0.003) {
        object->hit(this->mass * this->getVel().magnitude());
        this->alive = false;  // mark game object as dead
      }
    }
  }
}
