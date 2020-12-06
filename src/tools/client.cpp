#include "client.hpp"

Client::Client(const std::string& address, const unsigned int& port)
    : socket(address, port) {
  Log::info("client init");
}

Client::~Client() {}
