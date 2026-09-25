#include "label.hpp"

namespace heartCore { namespace graphics {
	Label::Label(std::string labelText, int scale, float x, float y, maths::vec4 color, Font font)
		: StaticSprite(maths::vec3(x,y,0), maths::vec3(0,0,0), color), m_text(labelText), m_scale(scale), m_font(font)
	{}
	void Label::submit(Renderer* renderer) const 
	{
		renderer->submitText(m_text, m_scale, m_position, m_color, m_font);
	}

	void Label::setScale(int scale) { m_scale = scale; }
	void Label::setFont(Font* font) { m_font = *font; }
} }