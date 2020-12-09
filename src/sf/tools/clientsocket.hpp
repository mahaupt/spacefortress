#pragma once
#include <cstring>
#include <string>

#include "log.hpp"
#include "netmsg.hpp"

#define CLIENT_SOCKET_BUFFER_SIZE 1024

class ClientSocket {
 public:
  ClientSocket(const std::string& address, const unsigned int& port);
  ~ClientSocket();

  bool isConnected() { return is_connected; }

 private:
  bool is_connected;
  int isocket;
  char ibuffer[CLIENT_SOCKET_BUFFER_SIZE];
  char obuffer[CLIENT_SOCKET_BUFFER_SIZE];

  unsigned int port;
  std::string address;
};
