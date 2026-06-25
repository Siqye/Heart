#include "label.hpp"
namespace heartCore { namespace graphics {
	Label::Label(std::string labelText, int x, int y, maths::vec4 color, const char* fontPath)
		: Sprite(x, y, 0, 0, color), m_text(labelText)
	{
		if (FT_Init_FreeType(&m_library)) {
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		}
		if (FT_New_Face(m_library, fontPath, 0, &m_face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		}
	}
} }