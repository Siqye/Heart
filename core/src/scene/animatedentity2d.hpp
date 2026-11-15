#pragma once
#include "entity2d.hpp"
#include "../utils/timer.hpp"

namespace heartCore {
	class AnimatedEntity2d : public Entity2d {
	private:
		Timer m_deltaTime;

		const float FIXED_TIMESTEP = 1.0f / 12.0f;

	public:
		AnimatedEntity2d(graphics::StaticSprite*, physics::ColideBox2d* hitBox);
		~AnimatedEntity2d();

		void update() override;
	};
}