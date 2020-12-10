#pragma once
#include <cstring>
#include <string>
#include <atomic>
#include <future>

#include "log.hpp"
#include "netmsg.hpp"
#include "basesocket.hpp"

class ClientSocket : public BaseSocket {
 public:
  ClientSocket(const std::string& address, const unsigned int& port);
  ~ClientSocket();
  
  void authenticate();
 private:
};
