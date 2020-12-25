#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "../gameobject.hpp"

#define NETMSG_HEADER_SIZE 4

enum class NetMsgType {
  // basic
  NONE = 0x00,
  PING = 0x01,
  PONG = 0x02,

  // AUTH & User Management
  AUTH = 0x10,
  AUTHREQUEST = 0x11,  // reserved for token based auth
  AUTHACCEPT = 0x12,
  AUTHDENY = 0x13,
  KICK = 0x20,
  BAN = 0x21,

  // join type
  CREW_CREATE = 0x31,
  CREW_JOIN = 0x32,    // text contains crew code
  CREW_ACCEPT = 0x33,  // text contains crew code

  // objects
  TEXT = 0x80,
  OBJECT = 0x81,

  // errors
  ERR_ = 0xE0,
  ERR_REQ = 0xE1,
  ERR_FULL = 0xE2,
  ERR_CREWNOTFOUND = 0xE3,
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
  Vec2 pos;
  Vec2 vel;
  double hull;
  double shield;
  char name[32];

  size_t getSize() { return 82; }
  void* getDataPtr() { return &(this->type); }
  NetMsgObject(GameObject* go) {
    if (go == nullptr) return;
    type = 0x10;
    pos = go->getPos();
    vel = go->getVel();
    hull = 0;
    shield = 0;
    strncpy(name, go->getName().c_str(), 32);
  }
  NetMsgObject(char* dataptr) {
    memcpy(&(this->type), dataptr, this->getSize());
  }
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
  NetMsg(const char* text, const NetMsgType& type = NetMsgType::TEXT) {
    data = new NetMsgText(text);
    size = (uint16_t)data->getSize();
    setType(type);
  }
  NetMsg(GameObject* go) {
    data = new NetMsgObject(go);
    size = (uint16_t)data->getSize();
    setType(NetMsgType::OBJECT);
  }

  // management functions
  size_t writeBuffer(char* buffer, size_t buffer_size) const;
  bool tryReadFromBuffer(char* buffer, size_t buffer_size);
  void setType(const NetMsgType& t) { this->type = (uint16_t)t; }

  // info functions
  size_t getSize() const { return this->size + NETMSG_HEADER_SIZE; }
};
#pragma pack(pop)
