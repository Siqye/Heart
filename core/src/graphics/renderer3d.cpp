#include "renderer3d.hpp"

namespace heartCore { namespace graphics {
	Renderer3d::Renderer3d() {
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(VAO);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(VERTEX_INDEX, 8, GL_FLOAT, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(UnitData3d, UnitData3d::vertex));
		glVertexAttribPointer(COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_FALSE, VERTEX_SIZE, (const GLvoid*)offsetof(UnitData3d, UnitData3d::color));
		glEnableVertexAttribArray(VERTEX_INDEX);
		glEnableVertexAttribArray(COLOR_INDEX);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		short indecies[INDECIES_SIZE];

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

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDECIES_SIZE, (const GLvoid*)indecies, GL_STATIC_DRAW);

		
	}


	Renderer3d::~Renderer3d() {}

	void Renderer3d::begin() {}
	void Renderer3d::submit(Object3d* object) {
		maths::vec3(-0.5f, -0.5f, 0.5f);  // 0			
		maths::vec3(0.5f, -0.5f, 0.5f);  // 1
		maths::vec3(0.5f, 0.5f, 0.5f);  // 2
		maths::vec3(-0.5f, 0.5f, 0.5f);  // 3

		maths::vec3(-0.5f, -0.5f, -0.5f);  // 4
		maths::vec3(0.5f, -0.5f, -0.5f);  // 5
		maths::vec3(0.5f, 0.5f, -0.5f);  // 6
		maths::vec3(-0.5f, 0.5f, -0.5f);  // 7
	}
	void Renderer3d::end() {}
	void Renderer3d::draw() {}
} }