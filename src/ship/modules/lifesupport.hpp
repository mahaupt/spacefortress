#pragma once

#include "../module.hpp"
#include "../ship.hpp"

class Lifesupport : public Module {
 public:
  Lifesupport(std::string name, double hull, double capacity);

  void simulate(double delta_time, Ship* ship);

 private:
  double capacity;
};
