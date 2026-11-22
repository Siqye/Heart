#pragma once
#include "../graphics/staticsprite.hpp"
#include "../graphics/frameanimation.hpp"
#include "../physics/colidebox.hpp"
#include <memory>

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
			
		std::vector<Animation> m_animations;

		bool m_isGrounded;
		bool m_isAttacking;

		EntityState m_entityState = EntityState::IDLE;


		std::shared_ptr<graphics::StaticSprite> m_visualisation;
		std::shared_ptr<physics::ColideBox2d> m_hitBox;

	public:
		// 1 entity = 1 sprite
		Entity2d(std::shared_ptr<graphics::StaticSprite> atlas, std::shared_ptr<physics::ColideBox2d> hitBox);

		virtual void render();
		virtual void update();
		virtual void tick();

		void impulse(maths::vec2 direction, float power);

		void startAnimation();
		void stopAnimation();

		maths::vec2& getPosition() { return m_position; }
		maths::vec2& getSize() { return m_size; }
		std::shared_ptr<graphics::StaticSprite> getVisual() { return m_visualisation; }
		std::shared_ptr<physics::ColideBox2d> getColideBox() { return m_hitBox; }
	};
}