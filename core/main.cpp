#include "src/utils/timer.hpp"
#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/renderer.hpp"
#include "src/graphics/texture.hpp"
#include "src/graphics/layers/group.hpp"
#include "src/graphics/layers/levellayer.hpp"


using namespace heartCore;
using namespace graphics;

int main() 
{
	Window window(800, 600, "Hello World");
	
	Shader shader("src/shader/basicVert.glsl", "src/shader/basicFrag.glsl");

	Group button(maths::mat4::rotation(35, maths::vec3(0,0,1)));

	LevelLayer layer;

	for (float x = 0; x < 4; x+=0.4f) { for (float y = 0; y < 3; y+=0.3f) {
		layer.add(Sprite(x,y,0.4,0.3,maths::vec4(1,1,1,1)));
	} }

	shader.bind();
	shader.setUniformMat4f("pr_matrix", maths::mat4::orthographic(0,4,3,0,1,0));
	shader.setUniform1i("tex", 0);

	Renderer renderer;
	glActiveTexture(GL_TEXTURE0);
	Texture tex("test/test.png");
	tex.bind();

	Timer timer;
	int fps = 0;


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
			timer.reset();
			fps = 0;
		}

		renderer.begin();
		layer.submit(&renderer);
		renderer.end();
		renderer.draw();

		window.update();
	}

	return 0;
}