#include "client.hpp"

Client::Client() : socket() {}

Client::Client(const std::string& address, const unsigned int& port,
               const std::string& username, const std::string& crewcode)
    : socket() {
  this->connect(address, port, username, crewcode);
}

/**
 * Connects client to server
 * @param address Server IP
 * @param port    Server Post
 */
void Client::connect(const std::string& address, const unsigned int& port,
                     const std::string& username, const std::string& crewcode) {
  this->socket.connect(address, port);
  if (socket.isConnected()) {
    socket.authenticate(username, crewcode);
    socket.startListener();
  }
}

/**
 * Properly disconnects and closes connection
 * Needs to be called before reconnection - to close socket and stop threads
 */
void Client::disconnect() {
  this->socket.disconnect();
  this->socket.close();
}

Client::~Client() {
#ifdef WIN32
  // windows cleanup
  WSACleanup();
#endif
}
