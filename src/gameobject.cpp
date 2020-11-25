#include "gameobject.hpp"

GameObject::GameObject() : GameObject("", 0, 0, false) {}

GameObject::GameObject(double x, double y, bool fixed)
    : GameObject("", x, y, fixed) {}

GameObject::GameObject(std::string name, double x, double y, bool fixed)
    : x(x),
      y(y),
      rot(0),
      is_fixed(fixed),
      name(name),
      vel_x(0),
      vel_y(0),
      force_x(0),
      force_y(0) {}

void GameObject::setPos(double x, double y) {
  this->x = x;
  this->y = y;
}

void GameObject::getPos(double &x, double &y) {
  x = this->x;
  y = this->y;
}

void GameObject::simulate(double delta_time) {
  // skip movement simulation on fixed object
  if (this->is_fixed) return;

  // apply velocity from force @todo consider mass
  this->vel_x += this->force_x * delta_time / 1000.0;
  this->vel_y += this->force_y * delta_time / 1000.0;

  // set maximum speed
  double vel = this->getVelAbs() * 1000.0;
  if (vel > 10.0) {
    double red = 10.0 / vel;
    this->vel_x *= red;
    this->vel_y *= red;
  }

  // reset tick force
  this->force_x = 0;
  this->force_y = 0;

  // apply position
  this->x += this->vel_x * delta_time;
  this->y += this->vel_y * delta_time;
}

void GameObject::applyForce(double fx, double fy) {
  this->force_x += fx;
  this->force_y += fy;
}
