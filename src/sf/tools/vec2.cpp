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

double Vec2::angle() const {
  double a = atan2(x, y);
  if (a < 0) {
    a += 3.1416 * 2;
  }
  return a;
}

Vec2& Vec2::operator=(const Vec2 other) {
  this->x = other.getX();
  this->y = other.getY();
  return *this;
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

double Vec2::operator*(const Vec2& vector) const {
  return this->magnitude() * vector.magnitude() *
         cos(vector.angle() - this->angle());
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

Vec2 Vec2::perpendicularClockwise() const { return Vec2(y, -x); }
Vec2 Vec2::perpendicularCounterClockwise() const { return Vec2(-y, x); }

Vec2 Vec2::getInterceptVel(const Vec2& spos, const Vec2& tpos, const Vec2& tvel,
                           const double& maxvel) {
  Vec2 vtgt = tpos - spos;
  vtgt.normalize();

  // trailing lead - when target is faster and moves away
  if (maxvel <= tvel.magnitude() && vtgt * tvel > 0) {
    return vtgt * maxvel;
  }

  // intercepting lead - when target is slower
  Vec2 vtgtn = vtgt.perpendicularClockwise();
  double transvel = vtgtn * tvel;
  double longvel = sqrt(maxvel * maxvel - transvel * transvel);
  Vec2 svel_tgt = vtgt * longvel + vtgtn * transvel;
  return svel_tgt;
}
