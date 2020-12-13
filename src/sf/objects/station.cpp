#include "station.hpp"

using namespace go;

Station::Station(const std::string& name, double x, double y)
    : GameObject(name, "Station", x, y, true) {
  this->symbol = L'I';
  this->is_dockable = true;
}
