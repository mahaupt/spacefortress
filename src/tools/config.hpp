#pragma once
#include <string>

#include "log.hpp"
#include "yaml-cpp/yaml.h"

class Config {
 public:
  Config();
  ~Config();

  static bool hasKey(const char* key);
  static std::string getStr(const char* key,
                            const std::string& default_val = "");
  static void setStr(const char* key, const std::string& val);

 private:
  static Config* self;

  YAML::Node config;
};
