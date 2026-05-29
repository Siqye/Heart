#include "src/graphics/window.hpp"
#include "src/graphics/shader.hpp"
#include "src/graphics/sprite.hpp"
#include "src/graphics/renderer.hpp"
#include "src/graphics/texture.hpp"


using namespace heartCore;
using namespace graphics;

int main() 
{
	Window window(800, 600, "Hello World");
	
	Shader shader("src/shader/basicVert.glsl", "src/shader/basicFrag.glsl");

	shader.bind();
	shader.setUniformMat4f("pr_matrix", maths::mat4::orthographic(0,4,3,0,1,0));
	shader.setUniform1i("tex", 0);
	
	Renderer renderer;
	Sprite sprite(1, 1, 0.5f, 0.5f, maths::vec4(1, 1, 1, 1));

	glActiveTexture(GL_TEXTURE0);
	Texture tex("test/test.png");
	tex.bind();

	double x, y;
	while (window.close()) {
		window.clear();

		renderer.begin();
		renderer.submit(&sprite);
		renderer.end();
		renderer.draw();

		window.update();
	}

	return 0;
}