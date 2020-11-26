#pragma once

#include <cmath>
#include <string>

class GameObject {
 public:
  GameObject();
  GameObject(double x, double y, bool fixed = false);
  GameObject(std::string name, std::string type, double x, double y,
             bool fixed = false);
  virtual ~GameObject() {}

  // getter and setters
  void setPos(double x, double y);
  void getPos(double &x, double &y);
  double getRot() { return this->rot; }
  void setRot(double rot) { this->rot = rot; }
  void setName(std::string name) { this->name = name; }
  std::string getName() { return this->name; }
  std::string getType() { return this->type; }
  std::string getSymbol() { return this->symbol; }
  bool isDockable() { return this->is_dockable; }
  void setFixed(bool f) { this->is_fixed = f; }
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
  bool is_dockable;
  std::string name;
  std::string type;
  std::string symbol;

  double vel_x;
  double vel_y;

  double force_x;
  double force_y;
};
