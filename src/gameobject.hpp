#pragma once

#include <cmath>
#include <string>

class GameObject {
 public:
  GameObject();
  GameObject(double x, double y, bool fixed = false);
  GameObject(std::string name, double x, double y, bool fixed = false);
  virtual ~GameObject() {}

  // getter
  void setPos(double x, double y);
  void getPos(double &x, double &y);
  double getRot() { return this->rot; }
  void setRot(double rot) { this->rot = rot; }
  void setName(std::string name) { this->name = name; }
  std::string getName() { return this->name; }
  std::string getSymbol() { return this->symbol; }
  double getVelAbs() { return sqrt(vel_x * vel_x + vel_y * vel_y); }
  void getVel(double &vx, double &vy) {
    vx = this->vel_x;
    vy = this->vel_y;
  }
  void getForce(double &fx, double &fy) {
    fx = this->force_x;
    fy = this->force_y;
  }
  void setForce(double fx, double fy) {
    this->force_x = fx;
    this->force_y = fy;
  }

  // simulation
  void applyForce(double fx, double fy);
  virtual void simulate(double delta_time);

 protected:
  double x;
  double y;
  double rot;
  bool is_fixed;
  std::string name;
  std::string symbol;

  double vel_x;
  double vel_y;

  double force_x;
  double force_y;
};
