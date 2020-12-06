#pragma once
#include <string>

#include "log.hpp"

class ServerSocket {
 public:
  ServerSocket(const std::string& address, const unsigned int& port);
  ~ServerSocket();

  // info functions
  bool isReady() { return is_ready; }

  // socket control
  int accept();

 private:
  bool is_ready;
  int isocket;
  char buffer[1024];

  unsigned int port;
  std::string address;
};
