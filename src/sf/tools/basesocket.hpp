#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")  // Winsock Library
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifdef WIN32
#define close closesocket
#define SHUT_RDWR SD_BOTH
#else
#define SOCKET int
#define INVALID_SOCKET 0
#endif

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
  void sendEmptyMsg(const NetMsgType &t);
  void ping();

  // win32 extra
  static bool initWsa();

 protected:
  // connection
  SOCKET isocket;
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

  // WIN32 extra
#ifdef WIN32
  static WSADATA wsaData;
#endif
  static bool wsa_initialized;
  static bool wsa_result;

  // startup
  bool createSocketClient();
  bool createSocketServer();

  // functions
  void listener();
  void parseiBuffer();
  virtual bool handleBaseMsg(std::shared_ptr<NetMsg> &pnmsg);
  virtual bool handleMsg(std::shared_ptr<NetMsg> &pnmsg) { return true; }
  void readAddress();
  SOCKET accept();
};
