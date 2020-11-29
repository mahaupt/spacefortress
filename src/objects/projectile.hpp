#pragma once

#include <string>

#include "../gameobject.hpp"

namespace go {
class Projectile : public GameObject {
 public:
  Projectile(const std::string &name, GameObject *origin, GameObject *target,
             double velocity);

  void simulate(double delta_time);

 private:
  GameObject *origin;
  GameObject *target;
};
}  // namespace go
