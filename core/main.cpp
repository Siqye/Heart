#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"


using namespace heartCore;
using namespace graphics;

int main() 
{
	Window window(800, 600, "Hello World");
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

	GLfloat vertices[] = {
		-0.5f,  0.5f, 0.0f, 1,		1.0f, 0.2f, 0.2f, 1.0f,
		 0.5f,  0.5f, 0.0f,	1,		0.2f, 1.0f, 0.2f, 1.0f,
		 0.5f, -0.5f, 0.0f,	1,		0.2f, 0.2f, 1.0f, 1.0f,
		 -0.5f, -0.5f, 0.0f,	1,		0.0f, 1.0f, 1.0f, 1.0f
	};

	GLushort indecies[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint VBO, VAO, IBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), indecies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0); glEnableVertexAttribArray(1);

	Shader shader("src/shader/basicVert.glsl", "src/shader/basicFrag.glsl");


	double x, y;
	while (window.close()) {
		window.clear();
		shader.bind();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		shader.unbind();
		window.update();
	}

	return 0;
}