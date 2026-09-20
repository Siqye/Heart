#include "font.hpp"

namespace heartCore {namespace graphics {
	Font::Font(const char* fontPath) {
		m_atlas = texture_atlas_new(512,512,4);
		m_font = texture_font_new_from_file(m_atlas, 128, fontPath);
	}
	
	texture_atlas_t* Font::getAtlas() { return m_atlas; }
	texture_font_t* Font::getFont() { return m_font; }
	const char* Font::getName() { return m_fontName;  }
} }