#include "lang.hpp"
Lang* Lang::self = 0;

Lang::Lang() {
  std::string lang = Config::getStr("lang", "en");
  Log::debug("Language: " + lang);

  this->db = YAML::LoadFile("lang/" + lang + ".yaml");
  Lang::self = this;

  // test
  if (Lang::get("lang") == lang) {
    Log::debug("Lang module loaded");
  } else {
    Log::debug("Error loading language");
  }
}

std::string Lang::get(std::string key) {
  if (Lang::self == 0) return key;
  YAML::Node node = Lang::self->db[key];

  // check if key avbl inline
  if (!node.IsDefined()) {
    return key;
  }

  return node.as<std::string>();
}

Lang::~Lang() { Lang::self = 0; }
