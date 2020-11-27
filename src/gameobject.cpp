#include "gameobject.hpp"

GameObject::GameObject() : GameObject("", "Object", 0, 0, false) {}

GameObject::GameObject(double x, double y, bool fixed)
    : GameObject("", "Object", x, y, fixed) {}

GameObject::GameObject(const std::string &name, const std::string &type,
                       double x, double y, bool fixed)
    : pos(x, y),
      rot(0),
      is_fixed(fixed),
      is_dockable(false),
      name(name),
      type(type) {}

void GameObject::simulate(double delta_time) {
  // skip movement simulation on fixed object
  if (this->is_fixed) {
    this->vel.zero();
    this->force.zero();
    return;
  }

  // apply velocity from force @todo consider mass
  this->vel += this->force * delta_time / 1000.0;

  // set maximum speed
  double vel = this->vel.magnitude() * 1000.0;
  if (vel > 10.0) {
    double red = 10.0 / vel;
    this->vel *= red;
  }

  // reset tick force
  this->force.zero();

  // apply position
  this->pos += this->vel * delta_time;
}

void GameObject::addForce(const Vec2 &force) { this->force += force; }
