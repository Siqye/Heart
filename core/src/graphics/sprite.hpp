#pragma once
#include "staticsprite.hpp"

namespace heartCore {
	namespace graphics {

		class Sprite : public StaticSprite {
		private:
			inline void setTC() {
				m_texCoords.push_back(maths::vec2(0, 0));
				m_texCoords.push_back(maths::vec2(0, 1));
				m_texCoords.push_back(maths::vec2(1, 1));
				m_texCoords.push_back(maths::vec2(1, 0));
			}
		public:
			Sprite(double x, double y, double width, double height, maths::vec4 color);

			Sprite(double x, double y, double width, double height, Texture* texture);

			void submit(Renderer* renderer) const override;
		};
	}
}