#include "star.hpp"

using namespace go;

Star::Star(std::string name, double x, double y)
    : GameObject(name, "Star", x, y, true) {
  this->symbol = "\u2600";  // 2605 // 26AA
}
