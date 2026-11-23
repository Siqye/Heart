#pragma once
#include "../../../ext/freetype-gl/freetype-gl.h"
#include <string>

namespace heartCore { namespace graphics { 
	namespace API {
	class Font {
	private:
		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
		
		std::string m_name;
		std::string m_filePath;
		
	public:
		Font(const std::string& fontPath, std::string fontName);
		~Font();

		texture_atlas_t* getAtlas();
		texture_font_t* getFont();
		inline const std::string& getName() { return m_name; }
	};
	}
} } 
