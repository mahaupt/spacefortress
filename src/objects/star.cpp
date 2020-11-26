#include "star.hpp"

using namespace go;

Star::Star(std::string name, double x, double y)
    : GameObject(name, "Star", x, y, true) {
  this->symbol = "\u26AA";  // 2605
}
