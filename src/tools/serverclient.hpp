#pragma once

#include <future>
#include <mutex>

#include "log.hpp"

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
  char ibuffer[1024];
  char obuffer[1024];

  std::future<void> fut_listener;

  void listener();
};
