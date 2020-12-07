#pragma once
#include <string>

#include "config.hpp"
#include "log.hpp"
#include "yaml-cpp/yaml.h"

class Lang {
 public:
  Lang();
  ~Lang();

  static std::string get(const char* key);

 private:
  static Lang* self;

  YAML::Node db;
};
