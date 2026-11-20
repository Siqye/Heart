#pragma once
#include <string>
#include <format>
#include <fstream>
#include <mutex>
#include <queue>
#include <string_view>
#include <condition_variable>

namespace heartCore {
    enum class LogLevel {
        Trace,
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
        std::string m_stringBuffer;
        LogLevel m_minLevel;
        const char* m_filePath;
        std::condition_variable m_condtionVar;
        std::mutex m_mutex;
        std::queue<LogEntry> m_logQueue;

    public:
        Logger(const char* logFilePath, LogLevel minLevel = LogLevel::Trace);
        ~Logger();

        void init();

        void log(LogEntry entry);
        void flush();

    private:
        std::string levelToString(LogLevel level);
	};
}