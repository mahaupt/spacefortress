#include "sensor.hpp"

using namespace shipos;

Sensor::Sensor(Ship* ship) : Program(ship), psensor(0) {}

Sensor::Sensor(Ship* ship, WindowAlignment alignment_x,
               WindowAlignment alignment_y, double size_x, double size_y)
    : Program(ship, alignment_x, alignment_y, size_x, size_y), psensor(0) {
  this->window->setTitle(Lang::get("program_sensor"));
}

void Sensor::render(ConsoleKey key) { Program::render(key); }