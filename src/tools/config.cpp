#include "config.hpp"

Config::Config() { fs.open("config.yaml"); }
void Config::read() {
  /*string buf;
  while (fs.getline(buf)) {
    // process line by line
    // cut comments
    auto pos = buf.find('#');
    if (pos >= 0) {
      buf = buf.substr(0, pos - 1);
    }

    // split :
    pos = buf.find(':');
    if (pos >= 0) {
      std::string var;
      std::string var;
    }
  }*/
}

Config::~Config() {
  if (this->fs.is_open()) {
    this->fs.close();
  }
}
