#pragma once

class GameObject {
 public:
  GameObject();
  void setPos(double x, double y);
  void getPos(double &x, double &y);
  double getRot() { return this->rot; }
  void setRot(double rot) { this->rot = rot; }
  void applyForce(double fx, double fy);

  virtual void simulate(double delta_time);

 protected:
  double x;
  double y;
  double rot;

  double vel_x;
  double vel_y;

  double force_x;
  double force_y;
};
