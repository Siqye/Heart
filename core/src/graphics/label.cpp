#include "label.hpp"

namespace heartCore { namespace graphics {
	Label::Label(std::string labelText, maths::vec3 position, maths::vec4 color) 
		: StaticSprite(position.x, position.y, 0,0, color), m_text(labelText)
	{}
	void Label::submit(Renderer* renderer) const {
		renderer->submitText(m_text, m_position, m_color);
	}
} }