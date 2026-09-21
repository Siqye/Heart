#pragma once
#include "../../ext/freetype-gl/freetype-gl.h"
#include <string>

namespace heartCore { namespace graphics { 
	class Font {
	private:
		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
	public:
		Font(std::string fontPath);
		~Font();

		texture_atlas_t* getAtlas();
		texture_font_t* getFont();
	};
} }
