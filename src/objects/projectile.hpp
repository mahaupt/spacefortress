#pragma once

#include <string>
#include <vector>

#include "../gameobject.hpp"

namespace go {
class Projectile : public GameObject {
 public:
  Projectile(std::vector<GameObject *> *pgobjects, const std::string &name,
             GameObject *origin, GameObject *target, double velocity);

  void simulate(double delta_time);

 private:
  GameObject *origin;
  GameObject *target;
  double lifetime;

  std::vector<GameObject *> *pgobjects;
};
}  // namespace go
