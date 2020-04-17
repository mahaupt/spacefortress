#include "module.hpp"

Module::Module(std::string name, float hull) : 
enabled(true), 
name(name), 
hull(hull), 
max_hull(hull)
{}