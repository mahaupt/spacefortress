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
  void disconnect();

  // info
  bool isAuthenticated() { return this->is_authenticated; }
  std::future<bool> getReadyForGameFuture();
  std::string getCrewCode() { return this->crew_code; }

 private:
  std::string crew_code;
  std::atomic<bool> is_authenticated;
  std::atomic<bool> is_crewmember;
  std::promise<bool> prom_ready_for_game;

  bool handleMsg(std::shared_ptr<NetMsg>& pnmsg) override;
};
