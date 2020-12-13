#pragma once
#include <memory>
#include <string>

#include "../sf/tools/basesocket.hpp"
#include "../sf/tools/clientsocket.hpp"
#include "../sf/tools/log.hpp"
#include "serverclient.hpp"

class ServerSocket : public BaseSocket {
 public:
  ServerSocket(const std::string& address, const unsigned int& port);
  ~ServerSocket();

  // info functions
  bool isReady() { return is_ready; }

  // socket control
  std::shared_ptr<ServerClient> accept();
  void unblock();

 private:
  bool is_ready;
};
