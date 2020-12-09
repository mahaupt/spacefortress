#include "gameobject.hpp"

GameObject::GameObject() : GameObject("", "Object", 0, 0, false) {}

GameObject::GameObject(double x, double y, bool fixed)
    : GameObject("", "Object", x, y, fixed) {}

GameObject::GameObject(const std::string &name, const std::string &type,
                       double x, double y, bool fixed)
    : alive(true),
      mass(1000),
      pos(x, y),
      rot(0),
      is_fixed(fixed),
      is_dockable(false),
      name(name),
      type(type) {}

void GameObject::simulate(double delta_time) {
  std::lock_guard<std::mutex> lock_guard(this->mx_object);
  
  // skip movement simulation on fixed object
  if (this->is_fixed) {
    this->vel.zero();
    this->force.zero();
    return;
  }

  // apply velocity from force @todo consider mass
  this->vel += this->force * delta_time / this->mass;

  // set maximum speed
  if (this->type != "Projectile") {
    double vel = this->vel.magnitude() * 1000.0;  // mAU/s
    if (vel > 10.0) {
      double red = 10.0 / vel;
      this->vel *= red;
    }
  }

  // reset tick force
  this->force.zero();

  // apply position
  this->pos += this->vel * delta_time;
}

void GameObject::addForce(const Vec2 &force) { this->force += force; }
