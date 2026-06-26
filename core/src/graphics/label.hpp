#pragma once
#include "sprite.hpp"
#include <string>
#include <ft2build.h> 
#include FT_FREETYPE_H


namespace heartCore { namespace graphics {
	class Label : public Sprite {
	private:
		std::string m_text;
		FT_Face m_face;
	public:
		Label(const char* label, int x, int y, maths::vec4 color, const char* fontPath);
		~Label();

		const std::string& getText() const;
		const FT_Face& getFace() const;
	};
} }