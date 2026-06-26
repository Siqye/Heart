#include "label.hpp"
<<<<<<< HEAD

namespace heartCore { namespace graphics {
	Label::Label(const char* label, int x, int y, maths::vec4 color, const char* fontPath)
		: Sprite(x,y,0,0,color),  m_text(label)
	{
		FT_Error error;
		FT_Library library;
		
		error = FT_Init_FreeType(&library);
		if (error) return;
		error = FT_New_Face(library, fontPath,0 , &m_face);
		if (error) return;
		const FT_GlyphSlot glyph = m_face->glyph;
		for (char c : m_text) {
			if (FT_Load_Char(m_face, c, FT_LOAD_RENDER) != 0);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
				glyph->bitmap.width, glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);
		}
	}

	Label::~Label() {}

=======
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
>>>>>>> f36fedf030899ced0ea5bd6422810c54baec6fa9
} }