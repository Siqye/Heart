#include "font.hpp"

namespace heartCore {namespace graphics {
	Font::Font(const char* fontPath, const char* m_name) {
		m_atlas = texture_atlas_new(512,512,4);
		m_font = texture_font_new_from_file(m_atlas, 64, fontPath);
	}

	Font::Font(const char* fontPath, const char* name, bool is_bold, bool is_italic, bool is_underscored) {

	}
	
	Font::~Font() {}

	texture_atlas_t* Font::getAtlas() { return m_atlas; }
	texture_font_t* Font::getFont() { return m_font; }
	//std::string Font::getName() { return m_fontName;  }
} }