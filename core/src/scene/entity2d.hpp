#pragma once
#include "../graphics/staticsprite.hpp"
#include "../graphics/frameanimation.hpp"
#include "../physics/colidebox.hpp"
#include <memory>
#include <unordered_map>

enum class EntityState {
	IDLE = 0,
	WALK,
	ATTACK,
	JUMP,
	RUN,
	SNEAK,

	CUSTOM_STATE1,
	CUSTOM_STATE2,
	CUSTOM_STATE3,
	CUSTOM_STATE4,
	CUSTOM_STATE5,
	CUSTOM_STATE6,
	CUSTOM_STATE7,
	CUSTOM_STATE8
};

struct EntityStateHash {
	std::size_t operator()(EntityState state) const noexcept {
		return static_cast<std::size_t>(state);
	}
};

struct AnimationState {
	EntityState state;
	int clip_id;
	int frame_idx;
	unsigned long long elapsed;
	bool finished;
	bool just_finished;
};

namespace heartCore {
	// 1 entity = 1 sprite
	class Entity2d {
	protected:
		maths::vec2& m_position;
		maths::vec2& m_size;
			
		std::unordered_map<EntityState, std::shared_ptr<graphics::Animation>, EntityStateHash> m_animations;

		bool m_isGrounded = false;
		bool m_isAttacking = false;

		EntityState m_entityState = EntityState::IDLE;
		EntityState m_requestedState = EntityState::IDLE;
		bool m_hasRequestedState = false;
		std::shared_ptr<graphics::Animation> m_currentAnimation;
		std::shared_ptr<graphics::Texture> m_textureBeforeAnimation;


		std::shared_ptr<graphics::StaticSprite> m_visualisation;
		std::shared_ptr<physics::ColideBox2d> m_hitBox;

	public:
		// 1 entity = 1 sprite
		Entity2d(std::shared_ptr<graphics::StaticSprite> atlas, std::shared_ptr<physics::ColideBox2d> hitBox);

		virtual void render();
		virtual void update();
		virtual void tick();

		void setState(EntityState state);
		EntityState getState() const { return m_entityState; }
		void setGrounded(bool grounded) { m_isGrounded = grounded; }
		void setAttacking(bool attacking) { m_isAttacking = attacking; }
		void setAnimation(EntityState state, std::shared_ptr<graphics::Animation> animation);

		void impulse(maths::vec2 direction, float power);

		void startAnimation();
		void stopAnimation();

		maths::vec2& getPosition() { return m_position; }
		maths::vec2& getSize() { return m_size; }
		std::shared_ptr<graphics::StaticSprite> getVisual() { return m_visualisation; }
		std::shared_ptr<physics::ColideBox2d> getColideBox() { return m_hitBox; }
	};
}