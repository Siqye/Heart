#include "font.hpp"

namespace heartCore {namespace graphics {
	Font::Font(const char* fontPath, const char* name) {
		m_atlas = texture_atlas_new(512,512,4);
		m_font = texture_font_new_from_file(m_atlas, 64, fontPath);
		m_name = name;
	}

	Font::Font(const char* fontPath, const char* name, bool is_bold, bool is_italic, bool is_underscored) 
		: m_isBold(is_bold), m_isItalic(is_italic), m_isUnderscored(is_underscored)
	{
		m_atlas = texture_atlas_new(512, 512, 4);
		m_font = texture_font_new_from_file(m_atlas, 64, fontPath);
		m_name = name;
	}
	
	Font::~Font() {}

	texture_atlas_t* Font::getAtlas() { return m_atlas; }
	texture_font_t* Font::getFont() { return m_font; }
	//std::string Font::getName() { return m_fontName;  }
} }