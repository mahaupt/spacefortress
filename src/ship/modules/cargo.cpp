#include "cargo.hpp"

Cargo::Cargo(std::string name, double hull, double capacity)
    : Module(name, hull, ModuleType::PASSIVE), capacity(capacity) {}
