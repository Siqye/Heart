#pragma once
#include "staticsprite.hpp"

namespace heartCore {
	namespace graphics {
		namespace API {
		class Sprite : public StaticSprite {
		public:
			Sprite(double x, double y, double width, double height, maths::vec4 color);

			Sprite(double x, double y, double width, double height, std::shared_ptr<Texture> texture);
		};
		}
	}
}