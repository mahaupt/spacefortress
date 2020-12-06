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

  Log::info("Server destroy");
}

void Server::start() {
  Log::info("starting server");
  this->is_running = true;
  this->client_thread = std::thread(&Server::client_handler, this);
}

void Server::stop() {
  Log::info("stopping server");
  {
    std::lock_guard<std::mutex> guard(this->mx_is_running);
    this->is_running = false;
  }
  this->client_thread.join();
}

void Server::client_handler() {
  Log::info("starting thread");
  while (this->isRunningSafe()) {
    this->socket.accept();
  }
  Log::info("stopping thread");
}

bool Server::isRunningSafe() {
  bool temp;
  {
    std::lock_guard<std::mutex> guard(this->mx_is_running);
    temp = this->is_running;
  }
  return temp;
}
