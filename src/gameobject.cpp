#include "gameobject.hpp"

GameObject::GameObject() {
  this->x = 0;
  this->y = 0;
  this->rot = 0;
}
void GameObject::setPos(double x, double y) {
  this->x = x;
  this->y = y;
}
void GameObject::getPos(double &x, double &y) {
  x = this->x;
  y = this->y;
}

void GameObject::simulate(double delta_time) {
  // apply velocity from force @todo consider mass
  this->vel_x += this->force_x * delta_time;
  this->vel_y += this->force_y * delta_time;

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
