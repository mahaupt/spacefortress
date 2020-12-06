#pragma once

#include <mutex>
#include <thread>

#include "serversocket.hpp"

class Server {
 public:
  Server(const std::string& address, const unsigned int& port);
  ~Server();

  void start();
  void stop();

 private:
  ServerSocket socket;
  bool is_running;
  std::mutex mx_is_running;

  std::thread client_thread;

  void client_handler();
  bool isRunningSafe();
};
