#include "cargo.hpp"

Cargo::Cargo(std::string name, double hull, double capacity)
    : Module(name, "Cargo", hull), capacity(capacity) {}
