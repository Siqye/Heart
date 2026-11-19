#include "frameanimation.hpp"

namespace heartCore { namespace graphics{
	Animation::Animation(std::vector<Texture*> frames, unsigned long long duration_ms, bool looping)
		: m_isPlaying(false), m_looping(looping), m_frameCount(frames.size()),
		 m_currentFrame(-1), m_duration(duration_ms), m_frames(std::move(frames))
	{ }
	

	void Animation::play() {
		if (!m_isPlaying) {
			m_isPlaying = true;
			m_deltaTime.start();
		}
	}

	void Animation::pause() {
		if (m_isPlaying) {
			m_isPlaying = false;
			m_deltaTime.stop();
		}
	}


	void Animation::nextSprite() {
		++m_currentFrame;

		if (m_currentFrame >= m_frameCount) {
			if (!m_looping) {
				reset();
				return;
			}

			m_currentFrame = 0;
		}

		m_currentFrameTexture = m_frames[m_currentFrame];
	}
	
	void Animation::reset() {
		m_currentFrameTexture = m_frames.empty() ? nullptr : m_frames[0];
		m_currentFrame = -1;

		m_isPlaying = false;
		m_deltaTime.reset();
	}
} }