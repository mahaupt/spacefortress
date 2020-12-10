#pragma once

#include <string>
#include <chrono>
#include <memory>

#include "../sf/tools/log.hpp"
#include "../sf/tools/netmsg.hpp"
#include "../sf/tools/basesocket.hpp"

#define CLIENT_BUFFER_SIZE 1024

class ServerClient : public BaseSocket {
 public:
  ServerClient(int socket);
  ~ServerClient();

 private:
  //user info
  bool is_authenticated;
  std::string name;
  std::chrono::system_clock::time_point connection_time;

  //
  void handleMsg(std::shared_ptr<NetMsg> pnmsg);
};
