#include "generator.hpp"


Generator::Generator(std::string name, double hull, double power_output, double fuel_consumption): 
Module(name, hull), 
max_power_output(power_output), 
max_fuel_consumption(fuel_consumption)
{
}

void Generator::simulate(double delta_time, Ship * ship)
{
    if (this->enabled == false) { return; }
    
    //try to add max power
    double fuel_available = ship->getFuel();
    double energy_output = max_power_output*delta_time;
    double fuel_needed = max_fuel_consumption*delta_time;
    
    //not enough fuel
    if (fuel_needed > fuel_available)
    {
        fuel_needed = fuel_available;
        energy_output = max_power_output/max_fuel_consumption*fuel_needed;
    }
    
    //try to save energy
    double real_energy_output = ship->addEnergy(energy_output);
    std::cout << "real_energy_output " << real_energy_output << std::endl;
    
    //not enough capacity
    if (real_energy_output < energy_output)
    {
        fuel_needed = max_fuel_consumption/max_power_output*real_energy_output;
    }
    
    //use fuel
    ship->useFuel(fuel_needed);
    std::cout << "fuel_needed " << fuel_needed << std::endl;
}