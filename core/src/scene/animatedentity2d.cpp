#include "animatedentity2d.hpp"

namespace heartCore {
	
	AnimatedEntity2d::AnimatedEntity2d(graphics::StaticSprite* sprite, physics::ColideBox2d* hitBox)
		: Entity2d(sprite, hitBox)
	{ }
	
	AnimatedEntity2d::~AnimatedEntity2d() {}

	void AnimatedEntity2d::update() {
		if (m_deltaTime.elapsed() >= FIXED_TIMESTEP) {
			m_visualisation->nextSprite();
			m_deltaTime.reset();
		}
	}
}