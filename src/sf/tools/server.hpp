#pragma once

#include <future>
#include <mutex>
#include <thread>
#include <vector>

#include "serverclient.hpp"
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

  std::thread new_client_acceptor;

  std::mutex mx_clients;
  std::vector<std::shared_ptr<ServerClient>> clients;

  void newClientAcceptor();
  bool isRunningSafe();
  void garbageCollector();
};
