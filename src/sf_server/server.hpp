#pragma once

#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

#include "serverclient.hpp"
#include "serversocket.hpp"

class Server {
 public:
  Server(const std::string& address, const unsigned int& port);
  ~Server();

  // management functions
  void start();
  void stop();
  
  // info functions
  bool isSocketReady() { return socket.isReady(); }
 private:
  ServerSocket socket;
  std::atomic<bool> is_running;

  std::thread new_client_acceptor;
  std::thread client_updater;

  std::mutex mx_clients;
  std::vector<std::shared_ptr<ServerClient>> clients;

  void newClientAcceptor();
  void clientUpdater();
  void garbageCollector();
};
