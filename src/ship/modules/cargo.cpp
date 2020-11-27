#include "cargo.hpp"

using namespace module;

Cargo::Cargo(const std::string &name, double hull, double capacity)
    : Module(name, "Cargo", hull), capacity(capacity) {}
