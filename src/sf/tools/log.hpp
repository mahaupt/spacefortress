#pragma once
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

enum class LogLevel {
  LL_OFF = 0,
  LL_FATAL = 1,
  LL_ERROR = 2,
  LL_WARN = 3,
  LL_INFO = 4,
  LL_DEBUG = 5,
  LL_TRACE = 6,
  LL_ALL = 7
};

class Log {
 public:
  Log(const char *file, const LogLevel &log_level = LogLevel::LL_ERROR);
  Log(const LogLevel &log_level = LogLevel::LL_ERROR);
  ~Log();

  void olog(const std::string &msg, const LogLevel &level = LogLevel::LL_INFO);
  const char *getLogLevelStr(const LogLevel &level);

  static void log(const std::string &msg,
                  const LogLevel &level = LogLevel::LL_INFO);
  static void fatal(const std::string &msg) {
    Log::log(msg, LogLevel::LL_FATAL);
  };
  static void error(const std::string &msg) {
    Log::log(msg, LogLevel::LL_ERROR);
  };
  static void warn(const std::string &msg) {
    Log::log(msg, LogLevel::LL_WARN);
  };
  static void info(const std::string &msg) {
    Log::log(msg, LogLevel::LL_INFO);
  };
  static void debug(const std::string &msg) {
    Log::log(msg, LogLevel::LL_DEBUG);
  };
  static void trace(const std::string &msg) {
    Log::log(msg, LogLevel::LL_TRACE);
  };
  static void all(const std::string &msg) { Log::log(msg, LogLevel::LL_ALL); };

 private:
  static Log *self;
  std::ostream *fs;
  LogLevel log_level;

  std::mutex mx_write;
};
