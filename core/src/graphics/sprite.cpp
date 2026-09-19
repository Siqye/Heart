#include "sprite.hpp"

namespace heartCore { namespace graphics {
	Sprite::Sprite(double x, double y, double width, double height, maths::vec4 color) 
		: StaticSprite(x, y, width, height, color)
	{ }

	Sprite::Sprite(double x, double y, double width, double height, Texture* texture)
		: StaticSprite(x, y, width, height, texture)
	{ }
} }