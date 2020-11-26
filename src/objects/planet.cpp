#include "planet.hpp"

using namespace go;

Planet::Planet(std::string name, double x, double y)
    : GameObject(name, "Planet", x, y, true) {
  this->symbol = "\u2205";
}
