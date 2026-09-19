#include "src/utils/timer.hpp"
#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/layers/group.hpp"
#include "src/graphics/layers/levellayer.hpp"
#include "src/graphics/renderer2d.hpp"
#include "src/graphics/label.hpp"
#include <memory>

using namespace heartCore;
using namespace graphics;
int main() 
{
	Window window(800, 600, "Heart");
	
	//glClearColor(0, 1, 1, 1);

	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");

	Texture* textures[] = {
		new Texture("test/test1.png"),
		new Texture("test/test2.png"),
		new Texture("test/test3.png"),
		new Texture("test/test4.png"),
		new Texture("test/test5.png")
	};

	LevelLayer layer;

	for (float x = 0; x < 4; x += 0.3f) { for (float y = 0; y < 3; y += 0.3f) {
		layer.add(std::make_unique<Sprite>(x, y, 0.25, 0.25, textures[rand() % 5]));
	} }

	int texIDs[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };

	shader.bind();
	shader.setUniformMat4f("pr_matrix", maths::mat4::orthographic(0,4,3,0,1,0));
	shader.setUniform1iv("textures", 32, texIDs);

	Renderer2d renderer;

	Timer timer;
	int fps = 0;
	std::string labelFPS = "0 fps";

	double x, y;
	while (window.close()) {
		window.clear();

		window.getMousePosition(x, y);
		shader.setUniform2f("ligth_pos", maths::vec2(
			-x * 4.0f / 800.0f,
			-3.0f + y * 3.0f / 600.0f
		));

		fps++;
		if (timer.elapsed() >= 1.0) {
			std::cout << fps << std::endl;
			labelFPS = std::to_string(fps);
			labelFPS += " fps";
			timer.reset();
			fps = 0;
		}

		layer.add(std::make_unique<Label>(labelFPS, maths::vec3(0.3f, 2.3f, 0), maths::vec4(1, 0, 1, 1)));
		layer.render(&renderer);
		layer.pop();

		window.update();
	}

	return 0;
}