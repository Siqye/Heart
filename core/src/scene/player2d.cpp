#include "player2d.hpp"

namespace heartCore {
	Player2d::Player2d(std::shared_ptr<graphics::StaticSprite> visual, std::shared_ptr<physics::ColideBox2d> hitBox) 
		: Entity2d(visual, hitBox)
	{}

	void Player2d::render() {}

	void Player2d::update() {}

	void Player2d::tick() {}
}