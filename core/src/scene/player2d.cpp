#include "player2d.hpp"

namespace heartCore {
	Player2d::Player2d(graphics::StaticSprite* visual, physics::ColideBox2d* hitBox) 
		: Entity2d(visual, hitBox)
	{}

	void Player2d::render() {}

	void Player2d::update() {}

	void Player2d::tick() {}
}