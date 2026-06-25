#pragma once 
#include "sprite.hpp"
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace heartCore { namespace graphics {
	class Label : public Sprite
	{
	public:
		Label(std::string labelText, int x, int y, maths::vec4 color,const char* fontPath);
		//~Label();
		//void submit(Renderer* renderer) override;
	private:
		std::string m_text;
		FT_Face m_face;
		FT_Library m_library;
	};
} }