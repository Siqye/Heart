#include "entity2d.hpp"
#include "../logger/logger.hpp"

namespace {
	heartCore::maths::vec2& requirePosition(const std::shared_ptr<heartCore::graphics::StaticSprite>& visual) {
		if (!visual)
			LOG_ERROR("Entity2d requires a visualisation");
		return visual->position;
	}

	heartCore::maths::vec2& requireSize(const std::shared_ptr<heartCore::graphics::StaticSprite>& visual) {
		if (!visual)
			LOG_ERROR("Entity2d requires a visualisation");
		return visual->size;
	}
}

namespace heartCore {
	Entity2d::Entity2d(std::shared_ptr<graphics::StaticSprite> visual, std::shared_ptr<physics::ColideBox2d> hitBox)
		: m_visualisation(visual),
		m_hitBox(hitBox),
		m_position(requirePosition(visual)),
		m_size(requireSize(visual))
	{ 
		if (!m_hitBox)
			LOG_ERROR("Entity2d requires a hitbox");
	}

	void Entity2d::update() {


		// added: updating before sync
		m_hitBox->update();
		// added: sync
		m_visualisation->update();
	}

	void Entity2d::tick() {}

	void Entity2d::render() {}

	void Entity2d::impulse(maths::vec2 direction, float power) {
		m_hitBox->impulse(direction, power);
	}


	void Entity2d::startAnimation() {
		m_visualisation->startAnimation();
	}

	void Entity2d::stopAnimation() {
	
	}

}