#pragma once

#include <cstring>
#include <future>
#include <mutex>
#include <atomic>
#include <string>
#include <chrono>

#include "../sf/tools/log.hpp"
#include "../sf/tools/netmsg.hpp"

#define CLIENT_BUFFER_SIZE 1024

class ServerClient {
 public:
  ServerClient(int socket);
  ~ServerClient();

  // management
  void startListener();
  void disconnect();

  // info
  bool isConnected();
  
  // rx tx
  void sendData(void* data, size_t size);

 private:
  // connection
  int isocket;
  std::atomic<bool> is_connected;
  std::mutex mx_socket_tx;
  char ibuffer[CLIENT_BUFFER_SIZE];
  size_t ibytes_avbl;
  char obuffer[CLIENT_BUFFER_SIZE];

  //info
  bool is_authenticated;
  std::string address;
  std::string name;
  std::chrono::system_clock::time_point connection_time;
  
  std::future<void> fut_listener;

  //
  void listener();
  void parseMsg();
};
