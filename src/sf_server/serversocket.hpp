#pragma once
#include <memory>
#include <string>

#include "../sf/tools/clientsocket.hpp"
#include "../sf/tools/log.hpp"
#include "serverclient.hpp"

class ServerSocket {
 public:
  ServerSocket(const std::string& address, const unsigned int& port);
  ~ServerSocket();

  // info functions
  bool isReady() { return is_ready; }

  // socket control
  std::shared_ptr<ServerClient> accept();
  void unblock();
  void close();

 private:
  bool is_ready;
  int isocket;
  char buffer[1024];

  unsigned int port;
  std::string address;
};
