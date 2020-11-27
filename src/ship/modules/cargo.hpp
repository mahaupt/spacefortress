#pragma once

#include "../module.hpp"

class Cargo : public Module {
 public:
  Cargo(const std::string &name, double hull, double capacity);

 private:
  double capacity;
};
