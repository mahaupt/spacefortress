#include "capacitor.hpp"


Capacitor::Capacitor(std::string name, double hull, double max_capacity, double max_power_input, double max_power_output) :
Module(name, hull),
energy(0),
max_capacity(max_capacity),
max_power_input(max_power_input), 
max_power_output(max_power_output)
{ }
