#pragma once

#include <cstdint>
#include <cstddef>
#include <string>

#define NETMSG_HEADER_SIZE 5

enum class NetMsgType { NONE = 0, PING = 1, TEXT = 10, OBJECT = 11 };

#pragma pack(push, 1)
class NetMsgData {
public:
  virtual ~NetMsgData() {}
  virtual size_t getSize() { return 0; }
  virtual void* getDataPtr() { return this; }
};

// 81 bytes
class NetMsgObject : public NetMsgData {
public:
  uint8_t type;
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

//variable size
class NetMsgText : public NetMsgData {
public:
  char * text;
  
  NetMsgText(): text(nullptr) {}
  NetMsgText(const char * text) {
    size_t length = strlen(text)+1; // also copy zero char for memory
    this->text = new char[length];
    memcpy(this->text, text, length);
  }
  NetMsgText(const char * text, size_t length) {
    this->text = new char[length+1];
    memcpy(this->text, text, length);
    //setting zero char at the end
    this->text[length] = '\x00';
  }
  ~NetMsgText() {
    if (text != nullptr) {
      delete text;
    }
  }
  
  size_t getSize()
  {
    if (text == nullptr) return 0;
    //not incl null character here -> not sending it over the network
    return strlen(text);
  }
  void* getDataPtr() { return text; }
};


class NetMsg {
 public:
  uint8_t type;
  uint32_t size;
  NetMsgData* data;

  NetMsg() : type(0), data(nullptr) {}
  ~NetMsg() { if(data != nullptr) { delete data; } }
  
  //msg types
  NetMsg(const char * text)
  : type((uint8_t)NetMsgType::TEXT)
  {
    data = new NetMsgText(text);
    size = data->getSize();
  }
  
  // management functions
  size_t writeBuffer(char* buffer, size_t buffer_size);
  bool tryReadFromBuffer(char* buffer, size_t buffer_size);
  
  // info functions
  size_t getSize() { return this->size + NETMSG_HEADER_SIZE; }
};
#pragma pack(pop)
