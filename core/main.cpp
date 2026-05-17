#include "src/graphics/window.hpp"

using namespace heartCore;
using namespace graphics;

int main() 
{
	Window window(800, 600, "Hello World");
	double x, y;
	while (window.close()) {
		window.clear();
		if (window.isKeyPressed(GLFW_KEY_A)) {
			std::cout << "A key is pressed" << std::endl;
		}
		window.getMousePosition(x,y);
		std::cout << "Mouse position: " << x << ", " << y << std::endl;
		window.update();
	}

	return 0;
}