#pragma once
#include <string>

#include "../gameobject.hpp"

namespace go {
class Station : public GameObject {
 public:
  Station(const std::string &name, double x, double y);

 private:
};
}  // namespace go
