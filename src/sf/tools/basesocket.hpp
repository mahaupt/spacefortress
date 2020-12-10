#pragma once

#include <future>
#include <mutex>
#include <atomic>
#include <string>
#include <memory>
#include <queue>

#include "log.hpp"
#include "netmsg.hpp"

#define BS_IBUFFER_SIZE 1024
#define BS_OBUFFER_SIZE 1024

class BaseSocket {
public:
  BaseSocket();
  virtual ~BaseSocket();
  
  // management
  void startListener();
  void disconnect();

  // info
  bool isConnected();
  double getLatency();
  
  // rx tx
  void sendData(void* data, size_t size);
  void ping();
protected:
  // connection
  int isocket;
  std::atomic<bool> is_connected;
  std::mutex mx_socket_tx;
  char ibuffer[BS_IBUFFER_SIZE];
  char obuffer[BS_OBUFFER_SIZE];
  size_t ibytes_avbl;
  double latency;
  std::chrono::steady_clock::time_point last_ping_sendtime;
  
  //info
  unsigned int port;
  std::string address;
  
  //threads
  std::future<void> fut_listener;
  
  //msg queue
  std::mutex mx_inc_msg;
  std::queue<std::shared_ptr<NetMsg>> inc_msg;
  
  //
  void listener();
  void parseiBuffer();
  virtual void handleMsg(std::shared_ptr<NetMsg> pnmsg);
};

