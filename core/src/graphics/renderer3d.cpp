#include "renderer3d.hpp"

namespace heartCore { namespace graphics {
	Renderer3d::Renderer3d() {
		m_indexCount = 0;

		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(UnitData3d, UnitData3d::vertex));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE, (const GLvoid*)offsetof(UnitData3d, UnitData3d::color));
		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);


		GLushort indecies[INDECIES_SIZE];

		for (int i = 0, o = 0; i < INDECIES_SIZE; i += 36, o += 8) {
			indecies[  i  ] = o;
			indecies[i + 1] = o + 1;
			indecies[i + 2] = o + 2;

			indecies[i + 3] = o + 2;
			indecies[i + 4] = o + 3;
			indecies[i + 5] = o;

			// Задняя грань
			indecies[i + 6] = o + 4;
			indecies[i + 7] = o + 6;
			indecies[i + 8] = o + 5;

			indecies[i + 9] = o + 6;
			indecies[i + 10] = o + 4;
			indecies[i + 11] = o + 7;

			// Левая грань
			indecies[i + 12] = o + 4;
			indecies[i + 13] = o;
			indecies[i + 14] = o + 3;
			
			indecies[i + 15] = o + 3;
			indecies[i + 16] = o + 7;
			indecies[i + 17] = o + 4;

			// Правая грань
			indecies[i + 18] = o + 1;
			indecies[i + 19] = o + 5;
			indecies[i + 20] = o + 6;
			
			indecies[i + 21] = o + 6;
			indecies[i + 22] = o + 2;
			indecies[i + 23] = o + 1;

			// Верхняя грань
			indecies[i + 24] = o + 3;
			indecies[i + 25] = o + 2;
			indecies[i + 26] = o + 6;

			indecies[i + 27] = o + 6;
			indecies[i + 28] = o + 7;
			indecies[i + 29] = o + 3;

			// Нижняя грань
			indecies[i + 30] = o + 4;
			indecies[i + 31] = o + 5;
			indecies[i + 32] = o + 1;

			indecies[i + 33] = o + 1;
			indecies[i + 34] = o;
			indecies[i + 35] = o + 4;
		}

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDECIES_SIZE, (const GLvoid*)indecies, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}


	Renderer3d::~Renderer3d() {}

	void Renderer3d::begin() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		m_bufferData = (UnitData3d*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void Renderer3d::submit(Object3d* object) {

		const maths::vec3 position = object->getPosition();
		const maths::vec3 size = object->getSize();
		const maths::vec4 colorV3 = object->getColor();

		int r = colorV3.x * 255.0f;
		int g = colorV3.y * 255.0f;
		int b = colorV3.z * 255.0f;
		int a = colorV3.w * 255.0f;

		unsigned int color = a << 24 | b << 16 | g << 8 | r;
		
		// 0
		m_bufferData->vertex = maths::vec3(position.x, position.y,position.z + size.z);
		m_bufferData->color = color;
		m_bufferData++;
		// 1
		m_bufferData->vertex = maths::vec3(position.x + size.x, position.y,position.z + size.z);
		m_bufferData->color = color;	
		m_bufferData++;
		// 2
		m_bufferData->vertex = maths::vec3(position.x + size.x, position.y + size.y, position.z + size.z);
		m_bufferData->color = color;
		m_bufferData++;
		// 3
		m_bufferData->vertex = maths::vec3(position.x, position.y + size.y, position.z + size.z);
		m_bufferData->color = color;
		m_bufferData++;
		//maths::vec3(-0.5f, -0.5f, 0.5f);  // 0			
		//maths::vec3(0.5f, -0.5f, 0.5f);  // 1
		//maths::vec3(0.5f, 0.5f, 0.5f);  // 2
		//maths::vec3(-0.5f, 0.5f, 0.5f);  // 3
		// 4
		m_bufferData->vertex = maths::vec3(position.x, position.y, position.z);
		m_bufferData->color = color;
		m_bufferData++;
		// 5
		m_bufferData->vertex = maths::vec3(position.x + size.x, position.y, position.z);
		m_bufferData->color = color;
		m_bufferData++;
		// 6
		m_bufferData->vertex = maths::vec3(position.x + size.x, position.x + size.y, position.z);
		m_bufferData->color = color;
		m_bufferData++;
		// 7
		m_bufferData->vertex = maths::vec3(position.x, position.y + size.y, position.z);
		m_bufferData->color = color;
		m_bufferData++;

		//maths::vec3(-0.5f, -0.5f, -0.5f);  // 4
		//maths::vec3(0.5f, -0.5f, -0.5f);  // 5
		//maths::vec3(0.5f, 0.5f, -0.5f);  // 6
		//maths::vec3(-0.5f, 0.5f, -0.5f);  // 7
	
		m_indexCount += 36;
	}
	void Renderer3d::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Renderer3d::draw() {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_indexCount = 0;
	}
} }