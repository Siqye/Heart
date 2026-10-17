#include "src/game.hpp"

int main()
{
	heartCore::Game game(800, 600, "my first c++ game");

	game.play();
	return 0;
}