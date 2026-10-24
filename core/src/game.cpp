#include "game.hpp"
#include <iostream>

namespace heartCore {
	Game::Game(int windowWidth, int windowHeight, const char* windowTitle) 
		:
		m_window(new Window(windowWidth, windowHeight, windowTitle)),
		m_shader(new Shader("src/shader/basic.vert", "src/shader/basic.frag")),
		m_mainGameLayer(m_shader),
		m_physManager(),
		m_playerSprite(new Sprite(1, 1, 5, 5, new Texture("test/test5.png"))),
		m_player(m_playerSprite, new physics::ColideBox2d(m_playerSprite->position, m_playerSprite->size, 10, 2.0f)),
		fpsLabel(Label("0 fps", 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf")))
	{

		m_mainGameLayer.add(m_playerSprite);
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
			m_player.impulse(maths::vec2(0, 1), 0.1f);
		else if (m_window->isKeyPressed(GLFW_KEY_S))
			m_player.impulse(maths::vec2(0, -1), 0.1f);
		if (m_window->isKeyPressed(GLFW_KEY_D))
			m_player.impulse(maths::vec2(1, 0), 0.1f);
		else if (m_window->isKeyPressed(GLFW_KEY_A))
			m_player.impulse(maths::vec2(-1, 0), 0.1f);

		m_player.update();
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