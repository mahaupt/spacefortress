#include "serversocket.hpp"

#ifdef WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  // Winsock Library
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

ServerSocket::ServerSocket(const std::string& address, const unsigned int& port)
    : is_ready(false), isocket(0), port(port), address(address) {
  // create socket
  if ((isocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Log::error("server socket creation failed");
    return;
  }

  // attaching socket
  int opt = 1;
  if (int n = setsockopt(isocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(int))) {
    Log::error("error setting up server socket: " + std::to_string(n));
    return;
  }

  // setup socket adress
  struct sockaddr_in oaddress;
  oaddress.sin_family = AF_INET;
  oaddress.sin_port = htons(8080);
  inet_aton(this->address.c_str(), &oaddress.sin_addr);

  if (::bind(isocket, (struct sockaddr*)&oaddress, sizeof(sockaddr_in)) < 0) {
    Log::error("server socket bind failed");
    return;
  }
  if (listen(isocket, 5) < 0) {
    Log::error("server socket listen failed");
    return;
  }

  Log::info("server socket created");

  this->is_ready = true;
}

ServerSocket::~ServerSocket() {
  if (isocket > 0) {
    ::close(isocket);
    Log::info("server socket closed");
  }
  isocket = 0;
}

std::shared_ptr<ServerClient> ServerSocket::accept() {
  struct sockaddr_in iaddress;

  int new_socket;
  if ((new_socket = ::accept(this->isocket, (struct sockaddr*)&iaddress,
                             (socklen_t*)&iaddress)) < 0) {
    return std::shared_ptr<ServerClient>(nullptr);
  }

  return std::make_shared<ServerClient>(new_socket);
}

/**
 * unblocks socket through quick and dirty connecting to self
 */
void ServerSocket::unblock() { ClientSocket cs(this->address, this->port); }
