#include "entity2d.hpp"

namespace heartCore {
	Entity2d::Entity2d(graphics::StaticSprite* visual, physics::ColideBox2d* hitBox)
		: m_visualisation(visual),
		m_hitBox(hitBox)
	{ 
		m_position = m_visualisation->position;
		m_size = m_visualisation->size;
	}

	void Entity2d::update() {
		// added: updating before sync
		m_hitBox->update();
		// added: sync
		m_visualisation->position = m_position;
	}

	void Entity2d::tick() {}

	void Entity2d::render() {}

	void Entity2d::impulse(maths::vec2 direction, float power) {
		m_hitBox->impulse(direction, power);
	}


	void Entity2d::startAnimation(float duration, int frameCount, bool loop) {
		
	}

	void Entity2d::stopAnimation() {
	
	}

}