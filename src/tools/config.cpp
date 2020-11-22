#include "config.hpp"

Config* Config::self = 0;

Config::Config() {
  this->config = YAML::LoadFile("config.yaml");

  Config::self = this;
  Log::debug("Config module loaded");

  for (YAML::const_iterator it = this->config.begin(); it != this->config.end();
       ++it) {
    if (it->second.IsScalar()) {
      Log::debug("conf " + it->first.as<std::string>() + ": " +
                 it->second.as<std::string>());
    }
  }
}

bool Config::hasKey(std::string key) {
  if (Config::self == 0) return false;
  return Config::self->config[key].IsDefined();
}

std::string Config::getStr(std::string key, std::string default_val) {
  if (Config::self == 0) return default_val;
  YAML::Node node = Config::self->config[key];

  // check if key avbl inline
  if (!node.IsDefined()) {
    return default_val;
  }

  return node.as<std::string>();
}

void Config::setStr(std::string key, std::string val) {
  if (Config::self == 0) return;
  YAML::Node node = Config::self->config[key];

  node = val;
}

Config::~Config() { Config::self = 0; }
