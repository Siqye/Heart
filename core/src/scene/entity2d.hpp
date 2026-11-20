#pragma once
#include "../graphics/staticsprite.hpp"
#include "../physics/colidebox.hpp"
#include <memory>


namespace heartCore {
	struct AnimationState {
		bool isPlaying = false;
		float currentTime = 0.0f;
		float duration = 0.0f;
		int currentFrame = 0;
		int totalFrames = 0;
		bool looping = false;
	};

	class Entity2d {
	protected:
		maths::vec2& m_position;
		maths::vec2& m_size;

		std::shared_ptr<graphics::StaticSprite> m_visualisation;
		std::shared_ptr<physics::ColideBox2d> m_hitBox;

		AnimationState m_animState;


	public:
		Entity2d(std::shared_ptr<graphics::StaticSprite> visual, std::shared_ptr<physics::ColideBox2d> hitBox);

		virtual void render();
		virtual void update();
		virtual void tick();

		void impulse(maths::vec2 direction, float power);

		void startAnimation();
		void stopAnimation();
		bool isAnimationPlaying() const { return m_animState.isPlaying; }

		maths::vec2& getPosition() { return m_position; }
		maths::vec2& getSize() { return m_size; }
		std::shared_ptr<graphics::StaticSprite> getVisual() { return m_visualisation; }
		std::shared_ptr<physics::ColideBox2d> getColideBox() { return m_hitBox; }
	};
}