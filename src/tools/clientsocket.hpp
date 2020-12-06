#pragma once
#include <string>

#include "log.hpp"

class ClientSocket {
 public:
  ClientSocket(const std::string& address, const unsigned int& port);
  ~ClientSocket();

  bool isReady() { return is_ready; }

 private:
  bool is_ready;
  int isocket;
  char buffer[1024];

  unsigned int port;
  std::string address;
};
