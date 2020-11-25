#pragma once
#include <string>

#include "../gameobject.hpp"

namespace go {
class Planet : public GameObject {
 public:
  Planet(std::string name, double x, double y);

 private:
};
}  // namespace go
