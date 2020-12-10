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



void ServerClient::handleMsg(std::shared_ptr<NetMsg> pnmsg) {
  // debug print out data
  std::string msg = this->address + ":" + std::to_string(this->port) + ": b" + std::to_string(pnmsg->getSize()) + " t" + std::to_string(pnmsg->type) + " : ";
  
  //handle message
  switch ((NetMsgType)pnmsg->type) {
    case (NetMsgType::AUTH): {
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      this->name = std::string(txt->text, pnmsg->size);
      this->is_authenticated = true;
      msg.append(txt->text, pnmsg->size);
      break;
    }
    case (NetMsgType::TEXT): {
      NetMsgText* txt = (NetMsgText*)pnmsg->data;
      msg.append(txt->text, pnmsg->size);
      break;
    }
    case (NetMsgType::INTENTION_CREATE):
      // create crew
      break;
      
    case (NetMsgType::INTENTION_JOIN):
      // join crew
      break;
      
    default:
      //nothing
      break;
  }
  
  Log::info(msg);
  
  BaseSocket::handleMsg(pnmsg);
}


