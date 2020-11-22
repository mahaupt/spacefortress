#include "lang.hpp"
Lang* Lang::self = 0;

Lang::Lang() {
  std::string lang = Config::getStr("lang", "en");
  Log::debug("Language: " + lang);

  try {
    this->db = YAML::LoadFile("lang/" + lang + ".yaml");
  } catch (...) {
    Log::error("could not open language file");
  }
  Lang::self = this;

  // test
  if (Lang::get("lang") == lang) {
    Log::info("language module loaded");
  } else {
    Log::error("error loading language");
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
