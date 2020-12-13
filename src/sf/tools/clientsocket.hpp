#pragma once
#include <atomic>
#include <cstring>
#include <future>
#include <string>

#include "basesocket.hpp"
#include "log.hpp"
#include "netmsg.hpp"

class ClientSocket : public BaseSocket {
 public:
  ClientSocket(const std::string& address, const unsigned int& port);
  ~ClientSocket();

  void authenticate();

 private:
};
