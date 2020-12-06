#pragma once

#include <cstring>
#include <future>
#include <mutex>

#include "log.hpp"
#include "netmsg.hpp"

#define CLIENT_BUFFER_SIZE 1024

class ServerClient {
 public:
  ServerClient(int socket);
  ~ServerClient();

  // management
  void startListener();

  // info
  bool isConnectedSafe();
  void disconnectClientSafe();

 private:
  int isocket;
  std::mutex mx_is_connected;
  bool is_connected;
  char ibuffer[CLIENT_BUFFER_SIZE];
  size_t ibytes_avbl;
  char obuffer[CLIENT_BUFFER_SIZE];

  std::future<void> fut_listener;

  void listener();
  void parseMsg();
};
