#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "log.hpp"
#include "netmsg.hpp"

#define BS_IBUFFER_SIZE 1024
#define BS_OBUFFER_SIZE 1024
#define BS_MSG_QUEUE_SIZE 24

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
  bool isMsgAvailable();
  std::string getAddress() { return this->address; }
  std::shared_ptr<NetMsg> popMessage();

  // rx tx
  void sendData(void *data, size_t size);
  void sendEmptyMsg(const NetMsgType & t);
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

  // info
  unsigned int port;
  std::string address;

  // threads
  std::future<void> fut_listener;

  // msg queue
  std::mutex mx_inc_msg;
  std::queue<std::shared_ptr<NetMsg>> inc_msg;

  //
  void listener();
  void parseiBuffer();
  virtual bool handleBaseMsg(std::shared_ptr<NetMsg> &pnmsg);
  virtual bool handleMsg(std::shared_ptr<NetMsg> &pnmsg) {}
};
