#pragma once
#include <string>

#include "../gameobject.hpp"

namespace go {
class Station : public GameObject {
 public:
  Station(std::string name, double x, double y);

 private:
};
}  // namespace go
