#pragma once
#include "../utils/cxxtimer.hpp"
#include "staticsprite.hpp"
#include "../logger/logger.hpp"

namespace heartCore { namespace graphics {
	class Animation {
	protected:
		Timer m_deltaTimer;

		bool m_looping;
		bool m_isPlaying;
		unsigned long long m_duration;
	public:
		Animation(unsigned long long m_duration, bool looping);

		virtual void play() = 0;
		virtual void pause() = 0;

		virtual void reset() = 0;
		virtual void nextSprite(std::shared_ptr<StaticSprite> sprite) = 0;

		inline const bool& isPlaying() { return m_isPlaying; }
		inline const bool& isLooping() { return m_looping; }
		inline const unsigned long long getDurationTime() { return m_duration; }
	};
} }