#pragma once
#include <string>

class Ship;

class Module
{
public:
    std::string name;
    
    bool enabled;
    
    float hull;
    float max_hull;

    Module(std::string name, float hull);
    virtual void simulate(float delta_time, Ship * ship) {};
};