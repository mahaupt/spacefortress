#pragma once
#include <ctime>
#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel {
  OFF = 0,
  FATAL = 1,
  ERROR = 2,
  WARN = 3,
  INFO = 4,
  DEBUG = 5,
  TRACE = 6,
  ALL = 7
};

class Log {
 public:
  Log(const LogLevel &log_level = LogLevel::ERROR);
  ~Log();

  void olog(const std::string &msg, const LogLevel &level = LogLevel::INFO);
  const char *getLogLevelStr(const LogLevel &level);

  static void log(const std::string &msg,
                  const LogLevel &level = LogLevel::INFO);
  static void fatal(const std::string &msg) { Log::log(msg, LogLevel::FATAL); };
  static void error(const std::string &msg) { Log::log(msg, LogLevel::ERROR); };
  static void warn(const std::string &msg) { Log::log(msg, LogLevel::WARN); };
  static void info(const std::string &msg) { Log::log(msg, LogLevel::INFO); };
  static void debug(const std::string &msg) { Log::log(msg, LogLevel::DEBUG); };
  static void trace(const std::string &msg) { Log::log(msg, LogLevel::TRACE); };
  static void all(const std::string &msg) { Log::log(msg, LogLevel::ALL); };

 private:
  static Log *self;
  std::fstream fs;
  LogLevel log_level;

  std::mutex mx_write;
};
