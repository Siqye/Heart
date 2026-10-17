#include "game.hpp"
#include <iostream>

namespace heartCore {
	Game::Game(int windowWidth, int windowHeight, const char* windowTitle) 
		:
		m_window(new Window(windowWidth, windowHeight, windowTitle)),
		m_shader(new Shader("src/shader/basic.vert", "src/shader/basic.frag")),
		m_mainGameLayer(m_shader),
		//m_speaker(Speaker()),
		m_player(1, 1, 1, 1, new Texture("test/test4.png"))
	{

		//m_player = Sprite(0, 0, 0.3, 0.3, new Texture("test/test4.png"));
		m_mainGameLayer.add(&m_player);
		m_playerSpeed = 0.5f;
		labelText = "0 fps";

		m_mainGameLayer.add(new Label(labelText, 1, 2.5f, 0.1f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf")));
	}

	// once per second
	void Game::tick() {
		return;
	}
	// 60 times per second
	void Game::update() {
		if (m_window->isKeyPressed(GLFW_KEY_W)) {
			std::cout << "up is pressed!" << "\n";
			m_player.position->y += m_playerSpeed;
		}
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
		while (m_window->close()) {
			m_window->clear();
			render();

			fps++;
			if (m_updatesCount <= 60) {
				update();
				m_updatesCount++;
			}

			if (m_timer.elapsed() >= 1.0f) {
				tick();
				labelText = std::to_string(fps);
				labelText += " fps";
				m_updatesCount = 0;
				m_timer.reset();
			}
			m_window->update();
		}
	}
}