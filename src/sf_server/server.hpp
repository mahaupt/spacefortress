#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "../sf/tools/config.hpp"
#include "../sf/tools/netmsg.hpp"
#include "crew.hpp"
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
  std::vector<Crew> crews;

  void newClientAcceptor();
  void clientUpdater();
  void garbageCollector();
  void msgHandler(const std::shared_ptr<ServerClient>& client,
                  const std::shared_ptr<NetMsg>& pnmsg);
  bool tryAddCrewMember(const std::shared_ptr<ServerClient>& client,
                        const std::string& crewcode);
  Crew* findCrewByCode(const std::string& code);
};
