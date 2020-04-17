#pragma once
#include <string>

class Ship;

class Module
{
public:
    std::string name;
    
    bool enabled;
    
    double hull;
    double max_hull;

    Module(std::string name, double hull);
    virtual void simulate(double delta_time, Ship * ship) {};
};