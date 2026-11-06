#include "jobsystem.h"

namespace heartCore { namespace threads {
	JobSystem::JobSystem() {
		init();
	}

	void JobSystem::init() {
        int coreCount = std::thread::hardware_concurrency();
        for (int i = 0; i < coreCount - 1; ++i) {
            m_workers.emplace_back([this] {
                while (m_isRunning) {
                    std::function<void()> job;
                    {
                        std::unique_lock<std::mutex> lock(m_queueMutex);
                        m_condition.wait(lock, [this] { return !m_jobQueue.empty() || !m_isRunning; });
                        if (!m_isRunning && m_jobQueue.empty()) return;
                        job = std::move(m_jobQueue.front());
                        m_jobQueue.pop();
                    }
                    job();
                }
            });
        }
	}

    void JobSystem::run(std::function<void()> job) {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_jobQueue.push(job);
        }
        m_condition.notify_one();
    }
} }