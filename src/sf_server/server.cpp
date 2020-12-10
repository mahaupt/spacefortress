#include "server.hpp"

Server::Server(const std::string& address, const unsigned int& port)
    : socket(address, port), is_running(false) {}

Server::~Server() {
  // try to stop server
  if (this->is_running) {
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
  this->client_updater = std::thread(&Server::clientUpdater, this);
}

void Server::stop() {
  Log::info("stopping server");
  
  // stopping threads
  this->is_running = false;
  this->socket.unblock();
  this->new_client_acceptor.join();
  this->client_updater.join();
  
  //close socket
  this->socket.close();
}

void Server::newClientAcceptor() {
  Log::info("starting client handler");
  while (this->is_running) {
    auto newclient = this->socket.accept();
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

void Server::clientUpdater() {
  Log::info("starting client updater");
  while (this->is_running) {
    this->garbageCollector();
    {
      std::lock_guard<std::mutex> guard(this->mx_clients);
      for (const auto & client : this->clients) {
        //update clients
        client->ping();
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  Log::info("stopping client updater");
}

/**
 * removes disconnected clients from memory
 */
void Server::garbageCollector() {
  std::lock_guard<std::mutex> guard(this->mx_clients);
  auto it = this->clients.begin();
  while (it != this->clients.end()) {
    // is dead object?
    if (!(*it)->isConnected()) {
      it = this->clients.erase(it);
    } else {
      it++;
    }
  }
}
