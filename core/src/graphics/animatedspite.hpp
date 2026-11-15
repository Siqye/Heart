#pragma once
#include "staticsprite.hpp"

namespace heartCore { namespace graphics {
	class AnimatedSprite : public StaticSprite {
	private:
		int m_spriteCount;
		int m_spriteIndex;

		int m_pixelWidth;
		int m_pixelHeight;
		
		std::vector<maths::vec2> m_spritesCoordsMin;
		std::vector<maths::vec2> m_spritesCoordsMax;

	public:
		AnimatedSprite(double x, double y, double width, double height, Texture* texture, int count, std::vector<maths::vec2> coordsMin, std::vector<maths::vec2> coordsMax);

		void nextSprite();
	};
} }