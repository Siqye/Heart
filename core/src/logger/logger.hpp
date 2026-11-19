#pragma once
#include <string>
#include <format>
#include <fstream>
#include <mutex>
#include <queue>
#include <string_view>

namespace heartCore {
    enum class LogLevel : int {
        Trace = 0,
        Debug,
        Info,
        Warn,
        Error,
        Fatal
    };

    struct LogEntry {
        LogLevel level;
        std::string message;
    };

	class Logger {
    private:
    public:
        Logger(const char* logFilePath, LogLevel minLevel = LogLevel::Trace);
        ~Logger();

        void Log(LogEntry entry);
        void flush();
	};
}