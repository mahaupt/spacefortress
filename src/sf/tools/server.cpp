#include "server.hpp"

Server::Server(const std::string& address, const unsigned int& port)
    : socket(address, port), is_running(false) {
  Log::info("Server init");
}

Server::~Server() {
  // try to stop server
  if (this->isRunningSafe()) {
    this->stop();
  }
  // disconnect all clients
  this->clients.clear();

  Log::info("Server destroy");
}

void Server::start() {
  Log::info("starting server");
  this->is_running = true;
  this->new_client_acceptor = std::thread(&Server::newClientAcceptor, this);
}

void Server::stop() {
  Log::info("stopping server");
  {
    std::lock_guard<std::mutex> guard(this->mx_is_running);
    this->is_running = false;
  }
  // unblocks client acceptor
  this->socket.unblock();
  this->new_client_acceptor.join();
}

void Server::newClientAcceptor() {
  Log::info("starting client handler");
  while (this->isRunningSafe()) {
    auto newclient = this->socket.accept();
    this->garbageCollector();
    if (newclient) {
      {
        std::lock_guard<std::mutex> guard(this->mx_clients);
        clients.push_back(newclient);
      }

      // start client listener
      newclient->startListener();
    }
  }
  Log::info("stopping client handler");
}

bool Server::isRunningSafe() {
  bool temp;
  {
    std::lock_guard<std::mutex> guard(this->mx_is_running);
    temp = this->is_running;
  }
  return temp;
}

/**
 * removes disconnected clients from memory
 */
void Server::garbageCollector() {
  std::lock_guard<std::mutex> guard(this->mx_clients);
  auto it = this->clients.begin();
  while (it != this->clients.end()) {
    // is dead object?
    if (!(*it)->isConnectedSafe()) {
      it = this->clients.erase(it);
    } else {
      it++;
    }
  }
}
