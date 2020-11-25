#include "station.hpp"

using namespace go;

Station::Station(std::string name, double x, double y)
    : GameObject(name, x, y, true) {
  this->symbol = 'I';
}
