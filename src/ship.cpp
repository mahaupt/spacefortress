#include "ship.hpp"

Ship::Ship(std::string name, double hull) :
modules(std::vector<Module*>())
{
    this->name = name;

    this->hull = hull;
    this->shield = 0;
    this->max_hull = hull;
    this->max_shield = 0;
}

Ship::~Ship()
{
    for(int i=0; i < this->modules.size(); i++)
    {
        delete this->modules[i];
    }
}



void Ship::info()
{
    std::cout << "Ship Info " << this->name << std::endl;
    std::cout << "Hull: " << this->hull << "/" << this->max_hull << std::endl;
    std::cout << "Shield: " << this->shield << "/" << this->max_shield << std::endl;
    std::cout << "Energy: " << this->getEnergyLevel() << "/" << this->getEnergyTotalCapacity() << std::endl;
    std::cout << this->modules.size() << " Modules installed" << std::endl;
}



void Ship::simulate(double delta_time)
{
    for(int i=0; i < this->modules.size(); i++)
    {
        this->modules[i]->simulate(delta_time, this);
    }
}



void Ship::addModule(Module *m)
{
    this->modules.push_back(m);
}



double Ship::getEnergy(double energy_needed)
{
    double energy_drawn = 0;

    //search
    for(int i=0; i < this->modules.size(); i++)
    {
        if (this->modules[i]->energy_available >= 0)
        {
            energy_drawn += this->modules[i]->getEnergy(energy_needed - energy_drawn);
            if (energy_drawn == energy_needed) {
                return energy_needed;
            }
        }
    }

    return energy_drawn;
}



double Ship::getEnergyLevel()
{
    double total_energy_avbl = 0;

    for(int i=0; i < this->modules.size(); i++)
    {
        if (this->modules[i]->type != GENERATOR)
        {
            total_energy_avbl += this->modules[i]->energy_available;
        }
    }

    return total_energy_avbl;
}


double Ship::getEnergyTotalCapacity()
{
    return 0;
}
