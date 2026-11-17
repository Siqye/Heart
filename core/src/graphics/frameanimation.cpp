#include "frameanimation.hpp"

namespace heartCore { namespace graphics{
	Animation::Animation(std::vector<Texture*> frames, float duration, bool looping) 
		: m_isPlaying(false), m_looping(looping), m_frameCount(frames.size()),
		m_timeStep(m_frameCount / duration), m_currentFrame(-1), m_duration(duration), m_frames(std::move(frames))
	{ }
	

	void Animation::play() {
		if (!m_isPlaying) {
			m_isPlaying = true;
		}
	}

	void Animation::pause() {
		if (m_isPlaying) {
			m_isPlaying = false;
			m_deltaTime.pause();
		}
	}

	void Animation::countinue() {
		if (!m_isPlaying) {
			m_isPlaying = false;
			m_deltaTime.resume();
		}
	}


	void Animation::nextSprite() {
		m_currentFrame++;
		if (m_currentFrame > m_frameCount) {
			m_currentFrame = 0;
			if (!m_looping) {
				reset();
			}
		}
		m_currentFrameTexture = m_frames[m_currentFrame];
	}
	
	void Animation::reset() {
		m_currentFrameTexture = nullptr;
		m_currentFrame = -1;

		m_isPlaying = false;
		m_deltaTime.reset();
	}
} }