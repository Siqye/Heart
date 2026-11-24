#define VULKAN

#ifndef VULKAN
#include "src/test.hpp"

int main()
{
	heartCore::Game game(800, 600, "my first c++ game");

	game.play();
	return 0;
}

#else

#include "src/graphics/API/window.hpp"

using namespace heartCore;
using namespace graphics;

int main() {
	API::Window window(800, 600, "vulkan test", API::RenderAPI::Vulkan);
	
	while (window.close()) {
		window.clear();
		
		window.update();
	}
}

#endif