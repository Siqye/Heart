#pragma once
#include "../graphics/staticsprite.hpp"
#include "../physics/colidebox.hpp"


namespace heartCore {
	class Entity2d {
	private:
		maths::vec2* m_position;
		maths::vec2* m_size;

		graphics::StaticSprite* m_visualisation;
		physics::ColideBox2d* m_hitBox;

	public:
		Entity2d(graphics::StaticSprite*, physics::ColideBox2d* hitBox);

		virtual void render();
		virtual void update();
		virtual void tick();

		void impulse(maths::vec2 direction, float power);

		maths::vec2* getPositionPTR() { return m_position; }
		maths::vec2* getSizePTR() { return m_size; }
		graphics::StaticSprite* getVisual() { return m_visualisation; }
	};
}