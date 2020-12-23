#include "config.hpp"

Config* Config::self = 0;

Config::Config(const std::string& file) : filename(file) {
  try {
    this->config = YAML::LoadFile(filename.c_str());
  } catch (...) {
    Log::error("could not open config file");
  }

  Config::self = this;
  Log::info("config module loaded");

  for (YAML::const_iterator it = this->config.begin(); it != this->config.end();
       ++it) {
    if (it->second.IsScalar()) {
      Log::debug("conf " + it->first.as<std::string>() + ": " +
                 it->second.as<std::string>());
    }
  }
}

Config::~Config() { Config::self = 0; }

bool Config::hasKey(const char* key) {
  if (Config::self == 0) return false;
  return Config::self->config[key].IsDefined();
}

template <typename T>
T Config::get(const char* key, const T default_val) {
  if (Config::self == 0) return default_val;
  YAML::Node node = Config::self->config[key];

  // check if key avbl inline
  if (!node.IsDefined()) {
    return default_val;
  }

  return node.as<T>();
}
template int Config::get<int>(const char* key, const int default_val = 0);
template std::string Config::get<std::string>(
    const char* key, const std::string default_val = "");

std::string Config::getStr(const char* key, const std::string& default_val) {
  return Config::get<std::string>(key, default_val);
}

void Config::setStr(const char* key, const std::string& val) {
  if (Config::self == 0) return;
  YAML::Node node = Config::self->config[key];

  node = val;
}

void Config::save() {
  if (Config::self == 0) return;
  std::ofstream fout(Config::self->filename.c_str());
  fout << Config::self->config;  // dump it back into the file
}
