#pragma once
#include <glew.h>
#include <vector>
#include "../maths/maths.hpp"
#include <cstddef>
#include "../../ext/freetype-gl/freetype-gl.h"

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
	class Sprite;
	struct VertexData;
	class Texture;
	
	class Renderer {
	private:
		std::vector<maths::mat4> m_transformStack;
		const maths::mat4* m_transformBack;

		std::vector<GLuint> m_textureSlots;

		GLuint VAO, VBO, IBO;
		GLsizei m_indexCount;
		VertexData* m_dataBuffer;

		// FTgl stuff
		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;

	public:
		Renderer();
		~Renderer();

		void push(const maths::mat4& matrix, bool override = false);
		void pop();

		void submit(const Sprite* sprite);
		void begin();
		void drawText(const std::string text, Texture fontTex, texture_font_t* font, maths::vec3 position, maths::vec4 col);
		void draw();
		void end();

	};
} }