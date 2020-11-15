#pragma once

#include <algorithm>

#include "../module.hpp"
#include "../ship.hpp"

class Capacitor : public Module
{
private:
    double energy;
    double max_capacity;
    double max_power_input;
    double max_power_output;

public:
    Capacitor(std::string name, double hull, double max_capacity, double max_power_input, double max_power_output);
    void simulate(double delta_time, Ship * ship);
};
