#include "generator.hpp"


Generator::Generator(std::string name, double hull, double power_output): 
Module(name, hull), 
max_power_output(power_output)
{
}

void Generator::simulate(double delta_time, Ship * ship)
{
    if (this->enabled == false) { return; }
    
    //try to add max power
    double energy_output = max_power_output*delta_time;
    
    //try to save energy
    double real_energy_output = ship->addEnergy(energy_output);
    std::cout << "real_energy_output " << real_energy_output << std::endl;
}