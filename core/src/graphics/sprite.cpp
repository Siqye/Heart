#include "sprite.hpp"

namespace heartCore { namespace graphics {
	Sprite::Sprite(double x, double y, double width, double height, maths::vec4 color) 
		: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), color)
	{ }

	Sprite::Sprite(double x, double y, double width, double height, Texture* texture)
		: StaticSprite(maths::vec2(x , y), maths::vec2(width, height), texture)
	{ }
} }