#define TEST3D

#ifndef TEST3D
#include "src/game.hpp"

int main()
{
	heartCore::Game game(800, 600, "my first c++ game");

	game.play();
	return 0;
}

#else

#include "src/graphics/window.hpp"
#include "src/graphics/renderer3d.hpp"
#include "src/graphics/shader.hpp"

using namespace heartCore;
using namespace graphics;

int main() {
	Window window(800, 600, "3dtest");

	Shader shader("src/shader/basic3d.vert", "src/shader/basic3d.frag");

	shader.bind();
	shader.setUniformMat4f("projection", maths::mat4::perspective(90, 4.0f / 3.0f, 0.1f, 50.0f));

	//shader.setUniformMat4f("projection", maths::mat4::orthographic(-40, 40, 30, -30, 10, 0));
	Renderer3d renderer;

	Object3d object(maths::vec3(-2.5f, -2.5f, -5.0f), maths::vec3(1.0f, 1.0f, 1.0f), maths::vec4(1, 0, 1, 1));
	
	while (window.close()) {
		window.clear();

		renderer.begin();
		renderer.submit(&object);
		renderer.end();
		renderer.draw();

		window.update();
	}
}

#endif