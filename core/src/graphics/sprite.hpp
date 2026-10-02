#pragma once
#include "staticsprite.hpp"

namespace heartCore {
	namespace graphics {
		class Sprite : public StaticSprite {
		public:
			Sprite(double x, double y, double width, double height, maths::vec4 color);

			Sprite(double x, double y, double width, double height, Texture* texture);
		};
	}
}