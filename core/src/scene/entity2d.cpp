#include "entity2d.hpp"
#include "../logger/logger.hpp"
#include <cmath>

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
		m_textureBeforeAnimation = m_visualisation->getTexture();
		if (!m_hitBox)
			LOG_ERROR("Entity2d requires a hitbox");
	}

	void Entity2d::update() {
		if (m_hitBox)
			m_hitBox->update();

		EntityState nextState = EntityState::IDLE;
		if (m_hasRequestedState) {
			nextState = m_requestedState;
			m_hasRequestedState = false;
		}
		else if (m_isAttacking) {
			nextState = EntityState::ATTACK;
		}
		else if (!m_isGrounded) {
			nextState = EntityState::JUMP;
		}
		else if ((std::abs(m_hitBox->speed.x) > 0.1f || std::abs(m_hitBox->speed.y) > 0.1f)) {
			nextState = EntityState::WALK;
		}

		const auto animation = m_animations.find(nextState);
		const bool stateChanged = nextState != m_entityState;
		const bool animationMissing = !m_currentAnimation;
		if (stateChanged || animationMissing) {
			if (m_currentAnimation)
				m_currentAnimation->pause();

			m_entityState = nextState;
			m_currentAnimation = animation != m_animations.end()
				? animation->second
				: nullptr;

			if (m_currentAnimation) {
				m_currentAnimation->reset();
				m_currentAnimation->nextSprite(m_visualisation);
				m_currentAnimation->play();
			}
			else {
				LOG_WARNING("Animation missing!");
			}
		}

		if (m_currentAnimation) {
			m_currentAnimation->play();
			m_currentAnimation->update(m_visualisation);
		} else {
			m_visualisation->setTC({ maths::vec2(0,0), maths::vec2(0,1), maths::vec2(1,1), maths::vec2(1,0) });
			m_visualisation->setTexture(m_textureBeforeAnimation);
		}
	}

	void Entity2d::tick() {}

	void Entity2d::render() {}

	void Entity2d::impulse(maths::vec2 direction, float power) {
		if (m_hitBox)
			m_hitBox->impulse(direction, power);
	}

	void Entity2d::setState(EntityState state) {
		m_requestedState = state;
		m_hasRequestedState = true;
	}

	void Entity2d::setAnimation(EntityState state, std::shared_ptr<graphics::Animation> animation) {
		if (animation)
			m_animations[state] = std::move(animation);
		else
			m_animations.erase(state);

		if (state == m_entityState) {
			m_currentAnimation = m_animations.contains(state) ? m_animations.at(state) : nullptr;
		}
	}

	void Entity2d::startAnimation() {
		if (m_currentAnimation)
			m_currentAnimation->play();
		else if (m_visualisation)
			m_visualisation->startAnimation();
	}

	void Entity2d::stopAnimation() {
		if (m_currentAnimation) {
			m_currentAnimation->pause();
			m_currentAnimation->reset();
			if (m_textureBeforeAnimation && m_visualisation) {
				m_visualisation->setTexture(m_textureBeforeAnimation);
				m_textureBeforeAnimation.reset();
			}
		}
		else if (m_visualisation) {
			m_visualisation->stopAnimation();
		}
	}

}