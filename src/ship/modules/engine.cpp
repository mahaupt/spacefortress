#include "engine.hpp"

Engine::Engine(std::string name, double hull, double max_thrust,
               double max_power)
    : Module(name, hull, ACTIVE),
      max_thrust(max_thrust),
      max_power(max_power) {}

void Engine::simulate(double delta_time, Ship *ship) {}
