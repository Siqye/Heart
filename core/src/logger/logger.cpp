#include "logger.hpp"

namespace heartCore {
	Logger::Logger(const char* logFilePath, LogLevel minLevel) 
		: m_filePath(logFilePath), m_minLevel(minLevel)
	{
		init();
	}

	void Logger::init() {
		while (!m_logQueue.empty()) {
			//m_condtionVar.wait(std::unique_lock<std::mutex> lock(m_mutex));
		}
	}

	void Logger::flush() {}

	void Logger::log(LogEntry entry) {
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_logQueue.push(entry);
		}
		m_condtionVar.notify_one();
	}

	std::string Logger::levelToString(LogLevel level) {
		switch (level) {
			case LogLevel::Trace:
				return "TRACE";
			case LogLevel::Debug:
				return "DEBUG";
			case LogLevel::Info:
				return "INFO";
			case LogLevel::Warn:
				return "WARN";
			case LogLevel::Error:
				return "ERROR";
			case LogLevel::Fatal:
				return "FATAL";
			default:
				return "UNKNOW";
		}
	}
}