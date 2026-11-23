#include "font.hpp"

namespace heartCore { namespace graphics {
	namespace API {
	Font::Font(const std::string& fontPath, std::string fontName) 
		: m_filePath(fontPath), m_name(fontName)
	{
		m_atlas = texture_atlas_new(512,512,4);
		m_font = texture_font_new_from_file(m_atlas, 64, fontPath.c_str());
	}
	
	Font::~Font() {}

	texture_atlas_t* Font::getAtlas() { return m_atlas; }
	texture_font_t* Font::getFont() { return m_font; }
	//std::string Font::getName() { return m_fontName;  }
	}
} }
