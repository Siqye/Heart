#pragma once
#include <glew.h>
#include "sprite.hpp"
#include <vector>
#include <cstddef>

#define MAX_SPRITES		10000
#define VERTEX_SIZE		sizeof(VertexData)
#define SPRITE_SIZE		VERTEX_SIZE * 4
#define BUFFER_SIZE		MAX_SPRITES * SPRITE_SIZE
#define INDICIES_SIZE	MAX_SPRITES * 6

#define VERTEX_INDEX		0
#define TEXTURE_COORD_INDEX 1
#define COLOR_INDEX			2
;

namespace heartCore { namespace graphics {
	class Renderer {
	private:
		std::vector<maths::mat4> m_transformStack;
		const maths::mat4* m_transformBack;

		GLuint VAO, VBO, IBO;
		GLsizei m_indexCount;
		VertexData* m_dataBuffer;
	public:
		Renderer();
		~Renderer();

		void push(const maths::mat4& matrix, bool override = false);
		void pop();

		void submit(const Sprite* sprite);
		void begin();
		void draw();
		void end();

	};
} }