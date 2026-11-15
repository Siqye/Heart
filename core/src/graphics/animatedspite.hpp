#pragma once
#include "staticsprite.hpp"

namespace heartCore { namespace graphics {
	class AnimatedSprite : public StaticSprite {
	private:
		int m_spriteCount;
		int m_spriteIndex;

	public:
		AnimatedSprite(double x, double y, double width, double height, Texture* texture, int count, std::vector<vec2> coords);

		void nextSprite();

	private:
		void clearUV();
	};
} }