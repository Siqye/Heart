#include "gamescene2d.hpp"

namespace heartCore {
	GameScene2d::GameScene2d(graphics::Window* window) : Scene2d(window)
	{
		m_graphicLayer.add(m_player->getVisual());
	}

	void GameScene2d::render() {
		m_graphicLayer.render();
	}
	
	void GameScene2d::update() {
		if (m_window->isKeyPressed(GLFW_KEY_W))
			m_player->impulse(maths::vec2(1, 0), 1.0f);

		if (m_window->isKeyPressed(GLFW_KEY_S))
			m_player->impulse(maths::vec2(-1, 0), 1.0f);

		if (m_window->isKeyPressed(GLFW_KEY_A))
			m_player->impulse(maths::vec2(0, -1), 1.0f);

		if (m_window->isKeyPressed(GLFW_KEY_D))
			m_player->impulse(maths::vec2(0, 1), 1.0f);
	}
	
	void GameScene2d::tick() {}
}