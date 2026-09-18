#pragma once
#include <string>
#include "staticsprite.hpp"


namespace heartCore { namespace graphics {
	class Label : public StaticSprite {
	private:
		std::string m_text;

	public:
		Label(std::string labelText, maths::vec3 position, maths::vec4 color);
		void submit(Renderer* renderer) const override;
	};
} }