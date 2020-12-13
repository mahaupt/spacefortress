#include "planet.hpp"

using namespace go;

Planet::Planet(const std::string &name, double x, double y)
    : GameObject(name, "Planet", x, y, true) {
  this->symbol = u8"\u2205";
}
