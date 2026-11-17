#include "timer.hpp"

namespace heartCore {
	Timer::Timer() {
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_start);
	}

	void Timer::pause() {
		if (!m_isPaused) {
			m_isPaused = true;
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
			m_beforePause = cycles * m_frequency;
		}
		
	}
	void Timer::resume() {
		if (m_isPaused) {
			m_isPaused = false;
			QueryPerformanceCounter(&m_start);
		}
	}

	void Timer::reset() {
		QueryPerformanceCounter(&m_start);
		m_beforePause = 0.0;
	}

	float Timer::elapsed() {
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
		return (float)(cycles * (m_frequency + m_beforePause));
	}
}