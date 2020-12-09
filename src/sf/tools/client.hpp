#pragma once

#include "clientsocket.hpp"

class Client {
 public:
  Client(const std::string& address, const unsigned int& port);
  ~Client();
  
  // info functions
  bool isConnected() { return socket.isConnected(); }
  
 private:
  ClientSocket socket;
};
