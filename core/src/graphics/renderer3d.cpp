#include "renderer3d.hpp"

namespace heartCore { namespace graphics {
	struct VertexData {
		maths::vec3 vertex;
		//maths::vec2 tc;
		//float tid;
		unsigned int color;
	};

	Renderer3d::Renderer3d() {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, 0, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::vertex));
		//glVertexAttribPointer(TEXTURE_COORD_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tc));
		//glVertexAttribPointer(TEXTURE_ID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
		glEnableVertexAttribArray(VERTEX_INDEX); 
		//glEnableVertexAttribArray(TEXTURE_COORD_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);
		//glEnableVertexAttribArray(TEXTURE_ID_INDEX); 
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint indecies[INDECIES_SIZE];

		for (int i = 0, o = 0; i < INDECIES_SIZE; i += 36, o += 9) {
			// лицевая сторона
			indecies[  i  ] = o;
			indecies[i + 1] = o + 1;
			indecies[i + 2] = o + 2;
			indecies[i + 3] = o;
			indecies[i + 4] = o + 3;
			indecies[i + 5] = o + 2;

			// левая сторона
			indecies[i + 6] = o;
			indecies[i + 7] = o + 1;
			indecies[i + 8] = o + 4;
			indecies[i + 9] = o;
			indecies[i + 10] = o + 5;
			indecies[i + 11] = o + 4;

			// правая сторона (переделать!!!)
			indecies[i + 12] = o + 5;
			indecies[i + 13] = o + 4;
			indecies[i + 14] = o + 7;
			indecies[i + 15] = o + 5;
			indecies[i + 16] = o + 6;
			indecies[i + 17] = o + 7;
			// нижнаяя сторона
			
			// верхняя сторона 
			
			// задняя сторона
		}

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), (const GLvoid*)indecies, GL_STATIC_DRAW);

	}

	void Renderer3d::begin() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		m_objectData = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer3d::submit(Object3d* object) {
		
	}

	void Renderer3d::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer3d::draw() {

	}
} }