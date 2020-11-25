#pragma once
#include <string>

#include "../gameobject.hpp"

namespace go {
class Star : public GameObject {
 public:
  Star(std::string name, double x, double y);

 private:
};
}  // namespace go
