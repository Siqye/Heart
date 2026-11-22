#pragma once
#include "animatedsprite.hpp"

namespace heartCore {
	namespace graphics {
		
		AnimatedSprite::AnimatedSprite(double x, double y, double width, double height, std::vector<std::shared_ptr<Texture>> frames)
			: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), frames.empty() ? nullptr : frames[0]), m_animation(frames, 1000, false)
		{
		}

		void AnimatedSprite::startAnimation() {
			m_animation.play();
		}

		void AnimatedSprite::stopAnimation() {
			m_animation.reset();
		}

		void AnimatedSprite::update() {
			m_animation.update(std::shared_ptr<StaticSprite>(this, [](StaticSprite*) {}));
		}

	}
}