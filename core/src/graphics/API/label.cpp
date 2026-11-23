#include "label.hpp"
#include <utility>

namespace heartCore { namespace graphics {
	namespace API {
	Label::Label(std::string labelText, int scale, float x, float y, maths::vec4 color, std::string font)
		: StaticSprite(maths::vec2(x,y), maths::vec2(0,0), color), m_text(labelText), m_scale(scale), m_font(font)
	{}
	void Label::submit(Renderer2D* renderer) const 
	{
		renderer->submitText(m_text, m_scale, m_position, m_color, m_font);
	}

	void Label::setScale(int scale) { m_scale = std::move(scale); }
	void Label::setText(std::string text) { m_text = std::move(text); }
	void Label::setFont(std::string font) { m_font = std::move(font); }

	}
} }
