#pragma once

#include "../module.hpp"
#include "../ship.hpp"

namespace module {
class Lifesupport : public Module {
 public:
  Lifesupport(const std::string& name, double hull, double capacity);

  void simulate(double delta_time, Ship* ship);

 private:
  double capacity;
};
}  // namespace module