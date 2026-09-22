#pragma once
#include "../../ext/freetype-gl/freetype-gl.h"
#include <string>

namespace heartCore { namespace graphics { 
	class Font {
	private:
		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
		bool m_isBold, m_isItalic, m_isUnderscored;
		const char* m_name;
	public:
		Font(const char* fontPath, const char* m_name);
		Font(const char* fontPath, const char* name, bool is_bold, bool is_italic, bool is_underscored);
		~Font();

		texture_atlas_t* getAtlas();
		texture_font_t* getFont();
	};
} }