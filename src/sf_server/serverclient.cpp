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

ServerClient::ServerClient(int socket) :
      is_authenticated(false),
      name("guest"),
      connection_time(std::chrono::system_clock::now())
{
  this->isocket = socket;
  this->is_connected = true;
  
  struct sockaddr_in address;
  size_t addrlen = sizeof(sockaddr_in);
  getpeername(isocket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
  this->address = inet_ntoa(address.sin_addr);
  this->port = ntohs(address.sin_port);

  Log::info("Client connected: " + this->address + ":" + std::to_string(this->port));
}

ServerClient::~ServerClient() {
  Log::info("Client disconnected: " + this->address + ":" + std::to_string(this->port));
}


/**
 * handle client based messages
 * other messages will be transfered to queue where server main queue will handle it
 */
bool ServerClient::handleMsg(std::shared_ptr<NetMsg> &pnmsg) {
  
  //handle message
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::AUTH): {
      if (this->is_authenticated) return false;
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      this->name = std::string(txt->text, pnmsg->size);
      this->is_authenticated = true;
      Log::info(this->address + ": authenticates as " + this->name);
      return false;
    }
    case (NetMsgType::TEXT): {
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      return true;
    }
    default:
      //nothing
      break;
  }
  
  return true;
}


