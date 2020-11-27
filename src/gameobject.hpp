#pragma once

#include <cmath>
#include <string>

#include "tools/vec2.hpp"

class GameObject {
 public:
  GameObject();
  GameObject(double x, double y, bool fixed = false);
  GameObject(const std::string &name, const std::string &type, double x,
             double y, bool fixed = false);
  virtual ~GameObject() {}

  // getter and setters
  void setName(const std::string &name) { this->name = name; }
  std::string getName() { return this->name; }
  std::string getType() { return this->type; }
  std::string getSymbol() { return this->symbol; }
  bool isDockable() { return this->is_dockable; }
  void setFixed(const bool &f) { this->is_fixed = f; }

  // position and motion
  void setPos(const Vec2 &pos) { this->pos = pos; }
  Vec2 getPos() { return this->pos; }
  double getRot() { return this->rot; }
  void setRot(const double &rot) { this->rot = rot; }
  Vec2 getVel() { return this->vel; }
  Vec2 getForce() { return this->force; }
  void setForce(const Vec2 &force) { this->force = force; }

  // simulation
  void addForce(const Vec2 &force);
  virtual void simulate(double delta_time);

 protected:
  Vec2 pos;
  double rot;
  bool is_fixed;
  bool is_dockable;
  std::string name;
  std::string type;
  std::string symbol;

  Vec2 vel;

  Vec2 force;
};
