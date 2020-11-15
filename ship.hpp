#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "module.hpp"

class Ship
{
private:
    std::string name;
    
    double hull;
    double shield;
    double energy_cap;
    double max_hull;
    double max_shield;
    double max_energy_cap;
    
    std::vector<Module*> modules;
    
public:
    Ship(std::string name, double hull);
    ~Ship();
    void simulate(double delta_time);
    void info();
    
    void addModule(Module *m);
    
    double getEnergy() { return energy_cap; }
    double addEnergy(double energy);
    //double useEnergy(double energy);
    
};

