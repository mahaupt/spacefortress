#pragma once
#include <iostream>
#include "../module.hpp"
#include "../ship.hpp"

class Generator : public Module
{
private:
    double max_power_output;
    double max_fuel_consumption;
    
public:
    Generator(std::string name, double hull, double power_output, double fuel_consumption);
    void simulate(double delta_time, Ship * ship);
};