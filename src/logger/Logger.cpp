/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#include "Logger.hpp"

namespace dwarfs {

const char* GetLogLevelString(LogLevel logLevel) {
    switch (logLevel) {
    case LogLevel::TRACE:   return "TRACE";
    case LogLevel::DEBUG:   return "DEBUG";
    case LogLevel::INFO:    return "INFO";
    case LogLevel::WARN:    return "WARN";
    case LogLevel::ERROR:   return "ERROR";
    default:                return "UNREACHABLE";
    }
}

int GetLogLevelIndex(LogLevel logLevel) {
    switch (logLevel) {
    case LogLevel::TRACE:   return 0;
    case LogLevel::DEBUG:   return 1;
    case LogLevel::INFO:    return 2;
    case LogLevel::WARN:    return 3;
    case LogLevel::ERROR:   return 4;
    default:                return -1;
    }
}

Logger::Logger(std::ostream& out_, LogLevel logLevel_) :
    out { out_ },
    logLevel { logLevel_ },
    mutex { } {
}

void Logger::WriteMessagePrefix(LogLevel msgLevel) {
  std::time_t t = std::time(nullptr);
  std::tm tm;
  if (localtime_s(&tm, &t) == 0) {
    out << std::put_time(&tm, "[%T] ");
  }
  else {
	out << "[NO_TIME] ";
  }
  out << GetLogLevelString(msgLevel) << " - ";
}

}   // namespace dwarfs
