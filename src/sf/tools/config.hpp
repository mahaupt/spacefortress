#pragma once
#include <fstream>
#include <string>

#include "log.hpp"
#include "yaml-cpp/yaml.h"

class Config {
 public:
  Config(const std::string& file);
  ~Config();

  static bool hasKey(const char* key);
  template <typename T>
  static T get(const char* key, const T default_val = T());
  static std::string getStr(const char* key,
                            const std::string& default_val = "");
  static void setStr(const char* key, const std::string& val);
  static void save();

 private:
  std::string filename;
  static Config* self;

  YAML::Node config;
};
