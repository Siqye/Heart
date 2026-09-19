#pragma once
#include <string>
#include "staticsprite.hpp"
#include "font.hpp"

namespace heartCore { namespace graphics {
	class Label : public StaticSprite {
	private:
		std::string m_text;
		int m_scale;
		Font m_font;

	public:
		Label(std::string labelText, int scale, maths::vec3 position, maths::vec4 color, Font font);
		void submit(Renderer* renderer) override;

		void setScale(int scale);
		void setFont(Font* font);
	};
} }