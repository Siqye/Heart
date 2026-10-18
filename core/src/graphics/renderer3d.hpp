#pragma once
#include <glew.h>
#include "object3d.hpp"
#include <cstddef>

#define MAX_OBJECTS		1000
#define VERTEX_SIZE		sizeof(UnitData3d)
#define OBJECT_SIZE		VERTEX_SIZE * 8
#define BUFFER_SIZE		MAX_OBJECTS * OBJECT_SIZE
#define INDECIES_SIZE	MAX_OBJECTS * 36

#define VERTEX_INDEX		0
#define COLOR_INDEX			1

namespace heartCore { namespace graphics {
	class Renderer3d {
	private:
		GLuint VBO, VAO, IBO;
		unsigned int m_indexCount;
		UnitData3d m_bufferData;
	public:
		Renderer3d();
		~Renderer3d();

		void begin();
		void submit(Object3d* object);
		void end();
		void draw();
	};
} }