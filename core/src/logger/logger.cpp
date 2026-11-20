#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger& Logger::Get()
{
    static Logger instance;
    return instance;
}

Logger::Logger()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localtime_s(&localTime, &time);

    std::stringstream filename;

    filename << std::put_time(&localTime, "%Y-%m-%d_%H-%M")
        << ".log";

    m_File.open(filename.str(), std::ios::out);

    log(LogLevel::INFO, "Logger initialized");
}

Logger::~Logger()
{
    log(LogLevel::INFO, "Logger shutdown");

    if (m_File.is_open())
        m_File.close();
}

void Logger::setMinLevel(LogLevel level)
{
    m_MinLevel = level;
}

const char* Logger::levelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::DEBUG:   return "DEBUG";
    case LogLevel::INFO:    return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::lERROR:   return "ERROR";
    case LogLevel::FATAL:   return "FATAL";
    default:               return "UNKNOWN";
    }
}

void Logger::log(LogLevel level, const std::string& message)
{
    if (level < m_MinLevel)
        return;

    if (!m_File.is_open())
        return;

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localtime_s(&localTime, &time);

    m_File
        << "["
        << std::put_time(&localTime, "%H:%M:%S")
        << "]["
        << levelToString(level)
        << "] "
        << message
        << '\n';

    m_File.flush();
}