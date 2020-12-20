#pragma once

#include "clientsocket.hpp"

class Client {
 public:
  Client();
  Client(const std::string& address, const unsigned int& port,
         const std::string& username, const std::string& crewcode = "");
  ~Client();

  // management functions
  void connect(const std::string& address, const unsigned int& port,
               const std::string& username, const std::string& crewcode = "");
  void disconnect();

  // info functions
  bool isConnected() { return socket.isConnected(); }

 private:
  ClientSocket socket;
};
