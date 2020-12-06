#include "serverclient.hpp"

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

ServerClient::ServerClient(int socket) : isocket(socket), is_connected(true) {
  struct sockaddr_in address;
  size_t addrlen = sizeof(sockaddr_in);
  getpeername(isocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
  std::string msg = "Client connected: ";
  msg += inet_ntoa(address.sin_addr);
  msg += ":";
  msg += std::to_string(ntohs(address.sin_port));
  Log::info(msg);
}

ServerClient::~ServerClient() {
  this->disconnectClientSafe();

  struct sockaddr_in address;
  size_t addrlen = sizeof(sockaddr_in);
  getpeername(isocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
  std::string msg = "Client disconnected: ";
  msg += inet_ntoa(address.sin_addr);
  msg += ":";
  msg += std::to_string(ntohs(address.sin_port));
  Log::info(msg);

  if (this->isocket > 0) {
    close(this->isocket);
    this->isocket = 0;
  }

  // join threads
  this->fut_listener.get();
}

void ServerClient::startListener() {
  this->fut_listener =
      std::async(std::launch::async, &ServerClient::listener, this);
}

void ServerClient::listener() {
  while (this->isConnectedSafe()) {
    size_t bytes = read(this->isocket, this->ibuffer, 1024);

    if (bytes <= 0) {
      this->disconnectClientSafe();
      break;
    }

    // todo: try to put buffer into queue...
    std::string msg = "Client: ";
    msg.append(this->ibuffer, bytes);
    Log::info(msg);
  }
}

bool ServerClient::isConnectedSafe() {
  bool temp;
  {
    std::lock_guard<std::mutex> guard(this->mx_is_connected);
    temp = this->is_connected;
  }
  return temp;
}

void ServerClient::disconnectClientSafe() {
  std::lock_guard<std::mutex> guard(this->mx_is_connected);
  this->is_connected = false;
}
