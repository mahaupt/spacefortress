#pragma once
#include <cmath>

class Vec2 {
 private:
  double x;
  double y;

 public:
  Vec2() : x(0), y(0){};
  ~Vec2(){};

  // initialization functions
  Vec2(const double& x, const double& y);
  Vec2(const Vec2& vector);
  static Vec2 fromAngle(const double& angle, const double& magnitude);

  // getters and setters
  double getX() const { return x; }
  double getY() const { return y; }
  void setX(const double& _x) { x = _x; }
  void setY(const double& _y) { y = _y; }
  double angle() const;

  // operators
  Vec2 operator+(const Vec2& vector) const;
  void operator+=(const Vec2& vector);
  Vec2 operator-(const Vec2& vector) const;
  void operator-=(const Vec2& vector);
  Vec2 operator*(const double& scalar) const;
  void operator*=(const double& scalar);
  double operator*(const Vec2& vector) const;
  Vec2 operator/(const double& scalar) const;

  // transformations
  void normalize();
  Vec2 normalized() const;
  double magnitude() const;
  Vec2 inverse() const;
  void zero() {
    this->x = 0;
    this->y = 0;
  }
  Vec2 perpendicularClockwise() const;
  Vec2 perpendicularCounterClockwise() const;

  // special functions
  static Vec2 getInterceptVel(const Vec2& spos, const Vec2& tpos,
                              const Vec2& tvel, const double& maxvel);
};