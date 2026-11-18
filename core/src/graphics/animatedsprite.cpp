#pragma once
#include "animatedsprite.hpp"

namespace heartCore {
	namespace graphics {
		
		AnimatedSprite::AnimatedSprite(double x, double y, double width, double height, std::vector<Texture*> frames)
			: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), frames.empty() ? nullptr : frames[0]), m_animation(frames, 1000, true)
		{
			m_timeStep = frames.empty() ? 0 : frames.size() / m_animation.getDurationTime();
		}

		void AnimatedSprite::startAnimation() {
			m_animation.play();
		}
		void AnimatedSprite::stopAnimation() {
			m_animation.pause();
		}

		void AnimatedSprite::update() {
			if (m_animation.isPlaying() || m_deltaTimer.count<std::chrono::microseconds>() >= m_timeStep) {
				m_animation.nextSprite();
				m_texture = m_animation.getCurrentTexture();
				
				m_deltaTimer.reset();
				m_deltaTimer.start();
			}
		}

	}
}