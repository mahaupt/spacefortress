#pragma once

#include <memory>
#include <string>
#include <vector>
#include <mutex>

#include "../gameobject.hpp"

namespace go {
class Projectile : public GameObject {
 public:
  Projectile(std::vector<std::shared_ptr<GameObject>> *pgobjects,
             const std::string &name, GameObject *origin,
             const std::shared_ptr<GameObject> &target, double velocity);

  void simulate(double delta_time);

 private:
  GameObject *origin;
  std::weak_ptr<GameObject> target;
  double lifetime;

  std::vector<std::shared_ptr<GameObject>> *pgobjects;
};
}  // namespace go
