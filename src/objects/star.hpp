#pragma once
#include <string>

#include "../gameobject.hpp"

namespace go {
class Star : public GameObject {
 public:
  Star(const std::string &name, double x, double y);

 private:
};
}  // namespace go
