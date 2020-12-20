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
  ClientSocket();
  ClientSocket(const std::string& address, const unsigned int& port);
  ~ClientSocket();

  void connect(const std::string& address, const unsigned int& port);
  void authenticate(const std::string& username,
                    const std::string& crewcode = "");

  bool isAuthenticated() { return this->is_authenticated; }

 private:
  std::atomic<bool> is_authenticated;

  bool handleMsg(std::shared_ptr<NetMsg>& pnmsg);
};
