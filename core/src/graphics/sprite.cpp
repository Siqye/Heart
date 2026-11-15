#include "sprite.hpp"

namespace heartCore { namespace graphics {
	Sprite::Sprite(double x, double y, double width, double height, maths::vec4 color) 
		: StaticSprite(maths::vec3(x, y, 0), maths::vec3(width, height, 1), color)
	{ }

	Sprite::Sprite(double x, double y, double width, double height, Texture* texture)
		: StaticSprite(maths::vec3(x , y, 0), maths::vec3(width, height, 1), texture)
	{ }
} }