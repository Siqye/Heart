#pragma once
#include "../../ext/freetype-gl/freetype-gl.h"

namespace heartCore { namespace graphics { 
	class Font {
	private:
		const char* m_fontName;
		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
	public:
		Font(const char* fontPath);
		//~Font();

		texture_atlas_t* getAtlas();
		texture_font_t* getFont();
		const char* getName();

	};
} }
