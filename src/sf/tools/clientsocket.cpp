#include "clientsocket.hpp"

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

ClientSocket::ClientSocket(const std::string& address, const unsigned int& port)
    : is_connected(false), isocket(0), port(port), address(address) {
      
  // create socket
  if ((isocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    Log::error("client socket creation failed");
    return;
  }

  // setup socket adress
  struct sockaddr_in oaddress;
  oaddress.sin_family = AF_INET;
  oaddress.sin_port = htons(8080);
  inet_aton(this->address.c_str(), &oaddress.sin_addr);

  if (connect(isocket, (struct sockaddr*)&oaddress, sizeof(sockaddr_in)) < 0) {
    Log::error("client socket connect failed");
    return;
  }

  Log::info("client socket created");

  NetMsg nmsg("Hello from client!");
  size_t bytes = nmsg.writeBuffer(this->obuffer, CLIENT_SOCKET_BUFFER_SIZE);
  send(isocket, this->obuffer, bytes, 0);

  this->is_connected = true;
}

ClientSocket::~ClientSocket() {
  if (isocket > 0) {
    close(isocket);
  }
  isocket = 0;
  Log::info("client socket closed");
}