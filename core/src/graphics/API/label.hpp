#pragma once
#include <string>
#include "staticsprite.hpp"
#include "font.hpp"

namespace heartCore { namespace graphics {
	namespace API {
	class Label : public StaticSprite {
	private:
		std::string m_text;
		int m_scale;
		std::string m_font;

	public:
		Label(std::string labelText, int scale, float x, float y, maths::vec4 color, std::string font);
		void submit(Renderer2D* renderer) const override;

		void setScale(int scale);
		void setText(std::string text);
		void setFont(std::string font);
	};
	}
} } 
