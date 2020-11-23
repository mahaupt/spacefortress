#pragma once
#include <ctime>
#include <fstream>
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
  Log(LogLevel log_level = LogLevel::ERROR);
  ~Log();

  void olog(std::string msg, LogLevel level = LogLevel::INFO);
  const char* getLogLevelStr(LogLevel level);

  static void log(std::string msg, LogLevel level = LogLevel::INFO);
  static void fatal(std::string msg) { Log::log(msg, LogLevel::FATAL); };
  static void error(std::string msg) { Log::log(msg, LogLevel::ERROR); };
  static void warn(std::string msg) { Log::log(msg, LogLevel::WARN); };
  static void info(std::string msg) { Log::log(msg, LogLevel::INFO); };
  static void debug(std::string msg) { Log::log(msg, LogLevel::DEBUG); };
  static void trace(std::string msg) { Log::log(msg, LogLevel::TRACE); };
  static void all(std::string msg) { Log::log(msg, LogLevel::ALL); };

 private:
  static Log* self;
  std::fstream fs;
  LogLevel log_level;
};
