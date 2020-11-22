#pragma once
#include <fstream>
#include <sstream>
#include <string>

#include "log.hpp"
#include "yaml-cpp/yaml.h"

class Config {
 public:
  Config();
  ~Config();

  static bool hasKey(std::string key);
  static std::string getStr(std::string key, std::string default_val = "");
  static void setStr(std::string key, std::string val);

 private:
  static Config* self;

  YAML::Node config;
};
