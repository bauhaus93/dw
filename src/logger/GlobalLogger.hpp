/* Copyright 2018 Jakob Fischer <JakobFischer93@gmail.com> */

#pragma once

#include <iostream>
#include <memory>

#include "Logger.hpp"
#include "LogLevel.hpp"

#ifdef NDEBUG
#define LOG_LEVEL INFO
#else
#define LOG_LEVEL DEBUG
#endif

namespace dwarfs {

void CreateGlobalLogger(std::ostream& output);
Logger& GetGlobalLogger();
bool GlobalLoggerActive();
void DestroyGlobalLogger();

#if LOG_LEVEL == TRACE
#define TRACE(args...) dwarfs::GetGlobalLogger().Trace(args)
#define DEBUG(args...) dwarfs::GetGlobalLogger().Debug(args)
#define INFO(args...) dwarfs::GetGlobalLogger().Info(args)
#define WARN(args...) dwarfs::GetGlobalLogger().Warn(args)
#define ERROR(args...) dwarfs::GetGlobalLogger().Error(args)
#elif LOG_LEVEL == DEBUG
#define TRACE(args...)
#define DEBUG(args...) dwarfs::GetGlobalLogger().Debug(args)
#define INFO(args...) dwarfs::GetGlobalLogger().Info(args)
#define WARN(args...) dwarfs::GetGlobalLogger().Warn(args)
#define ERROR(args...) dwarfs::GetGlobalLogger().Error(args)
#elif LOG_LEVEL == INFO
#define TRACE(args...)
#define DEBUG(args...)
#define INFO(args...) dwarfs::GetGlobalLogger().Info(args)
#define WARN(args...) dwarfs::GetGlobalLogger().Warn(args)
#define ERROR(args...) dwarfs::GetGlobalLogger().Error(args)
#elif LOG_LEVEL == WARN
#define TRACE(args...)
#define DEBUG(args...)
#define INFO(args...)
#define WARN(args...) dwarfs::GetGlobalLogger().Warn(args)
#define ERROR(args...) dwarfs::GetGlobalLogger().Error(args)
#elif LOG_LEVEL == ERROR
#define TRACE(args...)
#define DEBUG(args...)
#define INFO(args...)
#define WARN(args...) 
#define ERROR(args...) dwarfs::GetGlobalLogger().Error(args)
#endif

}   // namespace dwarfs
