#include "vec2.hpp"

Vec2::Vec2(const double& _x, const double& _y) {
  x = _x;
  y = _y;
}

Vec2::Vec2(const Vec2& vector) {
  x = vector.getX();
  y = vector.getY();
}

Vec2 Vec2::fromAngle(const double& angle, const double& magnitude) {
  return Vec2(sin(angle) * magnitude, cos(angle) * magnitude);
}

Vec2 Vec2::operator+(const Vec2& vector) const {
  return Vec2(x + vector.getX(), y + vector.getY());
}

void Vec2::operator+=(const Vec2& vector) {
  this->x += vector.getX();
  this->y += vector.getY();
}

Vec2 Vec2::operator-(const Vec2& vector) const {
  return Vec2(x - vector.getX(), y - vector.getY());
}

void Vec2::operator-=(const Vec2& vector) {
  this->x -= vector.getX();
  this->y -= vector.getY();
}

Vec2 Vec2::operator*(const double& scalar) const {
  return Vec2(x * scalar, y * scalar);
}

void Vec2::operator*=(const double& scalar) {
  this->x *= scalar;
  this->y *= scalar;
}

Vec2 Vec2::operator/(const double& scalar) const {
  return Vec2(x / scalar, y / scalar);
}

void Vec2::normalize() {
  double length = magnitude();
  x = x / length;
  y = y / length;
}

Vec2 Vec2::normalized() const {
  double length = magnitude();
  return Vec2(x / length, y / length);
}

double Vec2::magnitude() const { return sqrt(x * x + y * y); }

Vec2 Vec2::inverse() const { return Vec2(-x, -y); }