#pragma once

#include <string>
#include <chrono>
#include <memory>
#include <atomic>

#include "../sf/tools/log.hpp"
#include "../sf/tools/netmsg.hpp"
#include "../sf/tools/basesocket.hpp"

#define CLIENT_BUFFER_SIZE 1024

class ServerClient : public BaseSocket {
 public:
  ServerClient(SOCKET socket);
  ~ServerClient();
  
  //info functions
  bool isAuthenticated() { return is_authenticated; }
  bool isCrewmember() { return is_crewmember; }
  void setCrewmenber(bool crewmember) { is_crewmember = crewmember; }
  
 private:
  //user info
  std::atomic<bool> is_authenticated;
  std::atomic<bool> is_crewmember;
  std::string name;
  std::chrono::system_clock::time_point connection_time;

  //
  bool handleMsg(std::shared_ptr<NetMsg> &pnmsg);
};
