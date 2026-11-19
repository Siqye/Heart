#pragma once
#include "animatedsprite.hpp"

namespace heartCore {
	namespace graphics {
		
		AnimatedSprite::AnimatedSprite(double x, double y, double width, double height, std::vector<std::shared_ptr<Texture>> frames)
			: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), frames.empty() ? nullptr : frames[0]), m_animation(frames, 1000, false)
		{
			m_timeStep = frames.empty() ? 0 : m_animation.getDurationTime() * 1000 / frames.size();
		}

		void AnimatedSprite::startAnimation() {
			if (m_timeStep == 0)
				return;
			m_deltaTimer.start();
			m_animation.play();
		}
		void AnimatedSprite::stopAnimation() {
			m_animation.reset();
			m_deltaTimer.reset();
		}

		void AnimatedSprite::update() {
			//std::cout << m_deltaTimer.count<std::chrono::microseconds>() << "\n";

			if (!m_animation.isPlaying() || m_timeStep == 0)
				return;

			if (m_deltaTimer.count<std::chrono::microseconds>() >= m_timeStep) {
				m_animation.nextSprite();
				m_texture = m_animation.getCurrentTexture();
				
				m_deltaTimer.reset();
				m_deltaTimer.start();
			}
		}

	}
}