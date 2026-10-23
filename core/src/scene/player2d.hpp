#pragma once
#include "entity2d.hpp"

namespace heartCore {
	class Player2d : public Entity2d {
	private:
		graphics::StaticSprite m_HPSprites;

		int m_HP;
		int m_currentScore;
		int m_maxSessionScore;
	public:
		Player2d(graphics::StaticSprite* visual, physics::ColideBox2d* hitBox);

		void render() override;
		void update() override;
		void tick() override;
	};
}