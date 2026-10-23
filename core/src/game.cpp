#include "game.hpp"
#include <iostream>

namespace heartCore {
	Game::Game(int windowWidth, int windowHeight, const char* windowTitle) 
		:
		m_window(new Window(windowWidth, windowHeight, windowTitle)),
		m_shader(new Shader("src/shader/basic.vert", "src/shader/basic.frag")),
		m_mainGameLayer(m_shader),
		m_physManager(1),
		m_player(1, 1, 5, 5, new Texture("test/test5.png")),
		fpsLabel(Label("0 fps", 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf")))
	{

		

		m_mainGameLayer.add(&m_player);
		m_playerSpeed = 0.5f;
		fpsLabel_ptr = &fpsLabel;

		m_mainGameLayer.add(fpsLabel_ptr);
	}

	// once per second
	void Game::tick() {
		return;
	}
	// 60 times per second
	void Game::update() {
		if (m_window->isKeyPressed(GLFW_KEY_W)) 
			m_player.position->y += m_playerSpeed;
		else if (m_window->isKeyPressed(GLFW_KEY_S))
			m_player.position->y -= m_playerSpeed;
		if (m_window->isKeyPressed(GLFW_KEY_D))
			m_player.position->x += m_playerSpeed;
		else if (m_window->isKeyPressed(GLFW_KEY_A))
			m_player.position->x -= m_playerSpeed;
	}
	// unlimited per second
	void Game::render() {
		m_mainGameLayer.render();
	}

	void Game::play() {
		int fps = 0;
		std::string labelText;
		while (m_window->close()) {
			m_window->clear();
			render();

			fps++;
			if (m_updatesCount <= 30) {
				update();
				m_updatesCount++;
			}

			if (m_timer.elapsed() >= 1.0f) {
				tick();
				labelText = std::to_string(fps) + " fps";
				fpsLabel = Label(labelText, 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf"));
				m_updatesCount = 0;
				fps = 0;
				m_timer.reset();
			}
			m_window->update();
		}
	}
}