#include "serversocket.hpp"
#include "../sf/tools/basesocket.hpp"


/**
 * creates and binds to server socket. after successful, server can accept new clients
 */
ServerSocket::ServerSocket(const std::string& address, const unsigned int& port)
    : is_ready(false) {
  this->port = port;
  this->address = address;
      
  // Winsock WSA init
  if (!BaseSocket::initWsa()) return;
      
  // create socket
  if (!this->createSocketServer()) {
    return;
  }

  Log::info("server socket created");

  this->is_ready = true;
}

ServerSocket::~ServerSocket() {
  Log::info("server socket closed");
}

/**
 * function accepts new client, adds ServerClient wrapper and returns shared_ptr
 * blocking function
 */
std::shared_ptr<ServerClient> ServerSocket::accept() {

  SOCKET new_socket = BaseSocket::accept();
  if (new_socket == INVALID_SOCKET) {
    return std::shared_ptr<ServerClient>(nullptr);
  }

  return std::make_shared<ServerClient>(new_socket);
}

/**
 * unblocks socket through quick and dirty connecting to self
 */
void ServerSocket::unblock() { ClientSocket cs(this->address, this->port); }
