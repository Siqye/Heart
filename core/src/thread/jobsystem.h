#pragma once
#include <vector>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>

namespace heartCore { namespace threads {
	class JobSystem {
	private:
		std::vector<std::thread> m_workers;
		std::queue<std::function<void()>> m_jobQueue;
		std::mutex m_queueMutex;
		std::condition_variable m_condition;
		std::atomic<bool> m_isRunning;
	
	public:
		JobSystem();

		void run(std::function<void()> job);

	private:
		void init();
	};


} }