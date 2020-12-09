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

ServerClient::ServerClient(int socket)
    : isocket(socket), is_connected(true), ibytes_avbl(0) {
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

  //disconnect
  if (this->isocket > 0) {
    shutdown(this->isocket, SHUT_RDWR);
  }
  
  // join threads
  this->fut_listener.wait();
  
  // close socket
  if (this->isocket > 0) {
    close(this->isocket);
    this->isocket = 0;
  }
  
  Log::info(msg);
}

void ServerClient::startListener() {
  this->fut_listener =
      std::async(std::launch::async, &ServerClient::listener, this);
}

void ServerClient::listener() {
  while (this->isConnectedSafe()) {
    size_t free_buffer_size = CLIENT_BUFFER_SIZE - this->ibytes_avbl;
    void* buffer_start = this->ibuffer + this->ibytes_avbl;
    size_t bytes = read(this->isocket, buffer_start, free_buffer_size);
    this->ibytes_avbl += bytes;

    if (bytes <= 0) {
      this->disconnectClientSafe();
      break;
    }

    this->parseMsg();
  }
}

void ServerClient::parseMsg() {
  while (this->ibytes_avbl >= NETMSG_HEADER_SIZE) {
    
    // get message
    NetMsg nmsg;
    if (!nmsg.tryReadFromBuffer(this->ibuffer, this->ibytes_avbl)) {
      break;
    }

    // shift buffer
    size_t bytes_taken = nmsg.getSize();
    size_t bytes_remaining_in_buffer = this->ibytes_avbl - bytes_taken;
    memmove(this->ibuffer, this->ibuffer + bytes_taken,
            bytes_remaining_in_buffer);
    this->ibytes_avbl -= bytes_taken;

    // debug print out data
    std::string msg = "Client: ";
    NetMsgText *txt = (NetMsgText*)nmsg.data;
    msg.append(txt->text, nmsg.size);
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
