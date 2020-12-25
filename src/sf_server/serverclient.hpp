#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <string>

#include "../sf/tools/basesocket.hpp"
#include "../sf/tools/log.hpp"
#include "../sf/tools/netmsg.hpp"

#define CLIENT_BUFFER_SIZE 1024

class Crew;

class ServerClient : public BaseSocket {
 public:
  ServerClient(SOCKET socket);
  ~ServerClient();

  // info functions
  bool isAuthenticated() { return is_authenticated; }
  bool isCrewmember() { return is_crewmember; }
  void setCrewmenber(bool crewmember) { is_crewmember = crewmember; }
  void setCrew(const std::shared_ptr<Crew> &crew) { this->crew = crew; }
  std::shared_ptr<Crew> getCrew() { return this->crew.lock(); }

 private:
  // user info
  std::atomic<bool> is_authenticated;
  std::atomic<bool> is_crewmember;
  std::string name;
  std::chrono::system_clock::time_point connection_time;
  std::weak_ptr<Crew> crew;

  //
  bool handleMsg(std::shared_ptr<NetMsg> &pnmsg);
};
