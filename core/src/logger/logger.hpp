#pragma once

#include <fstream>
#include <string>

#define LOG_DEBUG(msg)      Logger::Log(LogLevel::DEBUG, msg);
#define LOG_INFO(msg)       Logger::Log(LogLevel::INFO, msg);
#define LOG_WARNING(msg)    Logger::Log(LogLevel::WARNING, msg);
#define LOG_ERROR(msg)      Logger::Log(LogLevel::ERROR, msg);
#define LOG_FATAL(msg)      Logger::Log(LogLevel::FATAL, msg);

enum class LogLevel
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

class Logger
{
public:
    static Logger& Get();

    void setMinLevel(LogLevel level);

    void log(LogLevel level, const std::string& message);

private:
    Logger();
    ~Logger();

    const char* levelToString(LogLevel level) const;

private:
    std::ofstream m_File;
    LogLevel m_MinLevel = LogLevel::DEBUG;
};