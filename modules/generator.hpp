#pragma once
#include <iostream>
#include "../module.hpp"
#include "../ship.hpp"

class Generator : public Module
{
private:
    double max_power_output;
    
public:
    Generator(std::string name, double hull, double power_output);
    void simulate(double delta_time, Ship * ship);
};