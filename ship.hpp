#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "module.hpp"

class Ship
{
private:
    std::string name;
    
    float hull;
    float shield;
    float fuel;
    float energy_cap;
    float max_hull;
    float max_shield;
    float max_fuel;
    float max_energy_cap;
    
    std::vector<Module*> modules;
    
public:
    Ship(std::string name, float hull, float fuel);
    ~Ship();
    void simulate(float delta_time);
    void info();
    
    void addModule(Module *m);
    
    float getEnergy() { return energy_cap; }
    float addEnergy(float energy);
    //float useEnergy(float energy);
    
    float addFuel(float fuel);
    float getFuel() { return fuel; }
    float useFuel(float fuel);
    
};

