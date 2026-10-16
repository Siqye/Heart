#pragma once
#include <glew.h>
#include "../maths/maths.hpp"
#include "mash.hpp"

#define MAX_MASHES 10'000
#define VERTEX_SIZE sizeof(VertexData)
#define MASH_SIZE VERTEX_SIZE * 8
#define BUFFER_SIZE MASH_SIZE * MAX_MASHES
#define INDECIES_SIZE MAX_MASHES * 36

#define VERTEX_INDEX 0
//#define TEXTURE_COORD_INDEX 1
//#define TEXTURE_ID_INDEX 2
#define COLOR_INDEX 1

namespace heartCore { namespace graphics {
	class Renderer3d {
	private:
		GLuint VBO, VAO, IBO;
		VertexData* m_objectData;

		GLsizei m_indexCount;
	public:
		Renderer3d();

		void begin();
		void submit(Object3d* object);
		void end();
		void draw();
	};
} }