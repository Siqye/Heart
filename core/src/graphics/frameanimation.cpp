#include "frameanimation.hpp"

namespace heartCore {
	namespace graphics {
		FrameAnimation::FrameAnimation(std::vector<std::shared_ptr<Texture>> frames, unsigned long long duration_ms, bool looping)
			: Animation(duration_ms, looping), m_frameCount(frames.size()),
			m_currentFrame(-1), m_currentFrameTexture(nullptr), m_frames(std::move(frames))
		{
		}


		void FrameAnimation::play() {
			if (!m_isPlaying && !m_frames.empty()) {
				m_isPlaying = true;
				m_deltaTimer.start();
			}
		}

		void FrameAnimation::pause() {
			if (m_isPlaying) {
				m_isPlaying = false;
				m_deltaTimer.stop();
			}
		}


		void FrameAnimation::nextSprite(std::shared_ptr<StaticSprite> sprite) {
			if (m_frames.empty()) {
				reset();
				return;
			}

			++m_currentFrame;

			if (m_currentFrame >= m_frameCount) {
				if (!m_looping) {
					reset();
					return;
				}

				m_currentFrame = 0;
			}

			sprite->setTexture(m_frames[m_currentFrame]);
		}

		void FrameAnimation::reset() {
			m_currentFrameTexture = m_frames.empty() ? nullptr : m_frames[0];
			m_currentFrame = -1;

			m_isPlaying = false;
			m_deltaTimer.reset();
		}
	}
}