#include "module.hpp"

Module::Module(std::string name, double hull) : 
enabled(true), 
name(name), 
hull(hull), 
max_hull(hull)
{}