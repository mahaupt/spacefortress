#include "ship.hpp"

Ship::Ship(std::string name, double hull, double fuel) :
modules(std::vector<Module*>())
{
    this->name = name;
    
    this->hull = hull;
    this->shield = 0;
    this->fuel = 0;
    this->max_hull = hull;
    this->max_fuel = fuel;
    this->max_shield = 0;
    
    this->energy_cap = 0;
    this->max_energy_cap = 10;
}

Ship::~Ship()
{
    for(int i=0; i < this->modules.size(); i++)
    {
        delete this->modules[i];
    }
}


void Ship::simulate(double delta_time)
{
    for(int i=0; i < this->modules.size(); i++)
    {
        this->modules[i]->simulate(delta_time, this);
    }
}

void Ship::info()
{
    std::cout << "Ship Info " << this->name << std::endl;
    std::cout << "Hull: " << this->hull << "/" << this->max_hull << std::endl;
    std::cout << "Shield: " << this->shield << "/" << this->max_shield << std::endl;
    std::cout << "Fuel: " << this->fuel << "/" << this->max_fuel << std::endl;
    std::cout << "Energy_cap: " << this->energy_cap << "/" << this->max_energy_cap << std::endl;
    std::cout << this->modules.size() << " Modules installed" << std::endl;
}


void Ship::addModule(Module *m)
{
    this->modules.push_back(m);
}


double Ship::addEnergy(double energy)
{
    this->energy_cap += energy;
    
    if (this->energy_cap > this->max_energy_cap)
    {
        double delta = this->max_energy_cap - this->energy_cap;
        this->energy_cap = this->max_energy_cap;
        return energy + delta;
    } else {
        return energy;
    }
}


double Ship::addFuel(double fuel)
{
    this->fuel += fuel;
    
    if (this->fuel > this->max_fuel)
    {
        double delta = this->max_fuel - this->fuel;
        this->fuel = this->max_fuel;
        return fuel + delta;
    } else {
        return fuel;
    }
}

double Ship::useFuel(double fuel)
{
    this->fuel -= fuel;
    
    if (this->fuel < 0)
    {
        double delta = this->fuel;
        this->fuel = 0;
        return fuel + delta;
    } else {
        return fuel;
    }
}



