#pragma once

#include <cmath>
#include <mutex>
#include <string>

#include "tools/vec2.hpp"

/**
 * gameobjects are defining the base of objects in the game.
 * can be derived to have custom properties
 */
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
  wchar_t getSymbol() { return this->symbol; }
  bool isDockable() { return this->is_dockable; }
  void setFixed(const bool &f) { this->is_fixed = f; }

  // position and motion
  void setPos(const Vec2 &pos) { this->pos = pos; }
  Vec2 getPos() { return this->pos; }
  Vec2 getPosSafe();
  double getRot() { return this->rot; }
  void setRot(const double &rot) { this->rot = rot; }
  Vec2 getVel() { return this->vel; }
  void setVel(const Vec2 &v) { this->vel = v; }
  Vec2 getForce() { return this->force; }
  void setForce(const Vec2 &force) { this->force = force; }
  bool isAlive() { return this->alive; }

  // simulation
  void addForce(const Vec2 &force);
  virtual void simulate(double delta_time);

  // manipulation
  virtual void hit(double energy){};

 protected:
  std::mutex mx_object;
  bool alive;
  double mass;
  Vec2 pos;
  double rot;
  bool is_fixed;
  bool is_dockable;
  std::string name;
  std::string type;
  wchar_t symbol;

  Vec2 vel;

  Vec2 force;
};
