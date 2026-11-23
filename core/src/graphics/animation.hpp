#pragma once
#include "../utils/cxxtimer.hpp"
#include "API/staticsprite.hpp"
#include "../logger/logger.hpp"

namespace heartCore { namespace graphics {
	using namespace API;
	class Animation {
	protected:
		Timer m_deltaTimer;

		bool m_looping;
		bool m_isPlaying;
		unsigned long long m_duration;
	public:
		Animation(unsigned long long duration, bool looping)
			: m_looping(looping), m_isPlaying(false), m_duration(duration) {}

		virtual void play() = 0;
		virtual void pause() = 0;

		virtual void reset() = 0;
		virtual void nextSprite(std::shared_ptr<API::StaticSprite> sprite) = 0;
		virtual void update(std::shared_ptr<StaticSprite> sprite) { (void)sprite; }
		virtual bool isFinished() const { return false; }

		inline const bool& isPlaying() { return m_isPlaying; }
		inline const bool& isLooping() { return m_looping; }
		inline const unsigned long long getDurationTime() { return m_duration; }
	};
} }