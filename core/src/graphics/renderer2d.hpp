#pragma once
#include "renderer.hpp"

#define MAX_SPRITES		10000
#define VERTEX_SIZE		sizeof(VertexData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		MAX_SPRITES * SPRITE_SIZE
#define INDICIES_SIZE	MAX_SPRITES * 6

#define VERTEX_INDEX		0
#define TEXTURE_COORD_INDEX 1
#define TEXTURE_ID_INDEX	2
#define COLOR_INDEX			3

namespace heartCore { namespace graphics {
	
	class Renderer2d : public Renderer {
	private:
		std::vector<GLuint> m_textureSlots;
		GLsizei m_indexCount;
		VertexData* m_dataBuffer;

		// FTgl stuff
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		ftgl::texture_glyph_t* m_FTGlyph;

	public:
		Renderer2d();
		~Renderer2d();

		void submit(const StaticSprite* sprite) override;
		void begin() override;
		void submitText(std::string text, maths::vec3 position, maths::vec4 col);
		void draw()	override;
		void end() override;

	};
} }