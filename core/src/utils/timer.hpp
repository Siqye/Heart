#pragma once
#include <Windows.h>

namespace heartCore {
	class Timer {
	private:
		LARGE_INTEGER m_start;
		double m_frequency;
	
		double m_beforePause;
		bool m_isPaused;;
	public:
		Timer();
		
		void pause();
		void resume();

		void reset();
		float elapsed();

		inline const bool& isPaused() { return m_isPaused; }
	};

}