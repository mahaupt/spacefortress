#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#define NETMSG_HEADER_SIZE 4

enum class NetMsgType {
  // basic
  NONE = 0,
  PING = 1,
  PONG = 2,

  // join type
  INTENTION_CREATE = 40,
  INTENTION_JOIN = 41,

  // AUTH & User Management
  AUTH = 50,
  AUTHREQUEST = 51,  // reserved for token based auth
  AUTHACCEPT = 52,
  AUTHDENY = 53,
  KICK = 60,
  BAN = 61,

  // objects
  TEXT = 100,
  OBJECT = 101,

  // errors
  ERR_ = 200,
  ERR_REQ = 201,
  ERR_FULL = 202,
  ERR_CREWNOTFOUND = 203,
};

#pragma pack(push, 1)
class NetMsgData {
 public:
  virtual ~NetMsgData() {}
  virtual size_t getSize() { return 0; }
  virtual void* getDataPtr() { return this; }
};

// 82 bytes
class NetMsgObject : public NetMsgData {
 public:
  uint16_t type;
  double x;
  double y;
  double vel_x;
  double vel_y;
  double hull;
  double shield;
  char name[32];

  size_t getSize() { return 81; }
  void* getDataPtr() { return this; }
};

// variable size
class NetMsgText : public NetMsgData {
 public:
  char* text;

  NetMsgText() : text(nullptr) {}
  NetMsgText(const char* text) {
    size_t length = strlen(text) + 1;  // also copy zero char for memory
    this->text = new char[length];
    memcpy(this->text, text, length);
  }
  NetMsgText(const char* text, size_t length) {
    this->text = new char[length + 1];
    memcpy(this->text, text, length);
    // setting zero char at the end
    this->text[length] = '\x00';
  }
  ~NetMsgText() {
    if (text != nullptr) {
      delete[] text;
    }
  }

  size_t getSize() {
    if (text == nullptr) return 0;
    // not incl null character here -> not sending it over the network
    return strlen(text);
  }
  void* getDataPtr() { return text; }
};

class NetMsg {
 public:
  uint16_t type;
  uint16_t size;
  NetMsgData* data;

  NetMsg() : type(0), size(0), data(nullptr) {}
  ~NetMsg() {
    if (data != nullptr) {
      delete data;
    }
  }

  // msg types
  NetMsg(const NetMsgType& type) : NetMsg() { this->setType(type); }
  NetMsg(const char* text) {
    data = new NetMsgText(text);
    size = (uint16_t)data->getSize();
    setType(NetMsgType::TEXT);
  }

  // management functions
  size_t writeBuffer(char* buffer, size_t buffer_size);
  bool tryReadFromBuffer(char* buffer, size_t buffer_size);
  void setType(const NetMsgType& t) { this->type = (uint16_t)t; }

  // info functions
  size_t getSize() { return this->size + NETMSG_HEADER_SIZE; }
};
#pragma pack(pop)
