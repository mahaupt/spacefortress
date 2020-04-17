#pragma once
#include <iostream>
#include "../module.hpp"
#include "../ship.hpp"

class Generator : public Module
{
private:
    float max_power_output;
    float max_fuel_consumption;
    
public:
    Generator(std::string name, float hull, float power_output, float fuel_consumption);
    void simulate(float delta_time, Ship * ship);
};