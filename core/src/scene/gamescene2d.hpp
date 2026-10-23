#pragma once

#include "scene2d.hpp"
#include "player2d.hpp"

namespace heartCore {
	class GameScene2d : public Scene2d {
	private:
		Player2d* m_player;

	public:
		GameScene2d();

		void render() override; // no limit per second
		void update() override; // 60 times per second
		void tick() override; // 1 per second
	};
}