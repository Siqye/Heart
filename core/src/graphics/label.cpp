#include "label.hpp"

namespace heartCore { namespace graphics {
	Label::Label(std::string labelText, int scale, maths::vec3 position, maths::vec4 color, Font font)
		: StaticSprite(position.x, position.y, 0,0, color), m_text(labelText), m_scale(scale), m_font(font)
	{}
	void Label::submit(Renderer* renderer) {
		renderer->submitText(m_text, m_scale, m_position, m_color, m_font);
	}

	void Label::setScale(int scale) { m_scale = scale; }
	void Label::setFont(Font* font) { m_font = *font; }
} }