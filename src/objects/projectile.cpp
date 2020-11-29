#include "projectile.hpp"

using namespace go;

Projectile::Projectile(const std::string &name, GameObject *origin,
                       GameObject *target, double velocity)
    : GameObject(name, "Projectile", 0, 0), origin(origin), target(target) {
  this->symbol = "\u2219";
  Vec2 spos = origin->getPos();
  this->setPos(spos);

  Vec2 vel =
      Vec2::getInterceptVel(spos, target->getPos(), target->getVel(), velocity);
  this->setVel(vel);
}

void Projectile::simulate(double delta_time) {
  GameObject::simulate(delta_time);
}