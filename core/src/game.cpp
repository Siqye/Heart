#include "game.hpp"
#include <iostream>

namespace heartCore {
	Game::Game(int windowWidth, int windowHeight, const char* windowTitle) 
		:
		m_window(new Window(windowWidth, windowHeight, windowTitle)),
		m_shader(new Shader("src/shader/basic.vert", "src/shader/basic.frag")),
		m_mainGameLayer(m_shader),
		m_physManager(),
		m_playerSprite(new AnimatedSprite(1, 1, 5, 5, {new Texture("test/test1.png"),new Texture("test/test2.png"), new Texture("test/test3.png")})),
		m_player(m_playerSprite, new physics::ColideBox2d(m_playerSprite->position, m_playerSprite->size, 10, 2.0f)),
		m_jobSystem(),
		m_accumulator(0.0f),
		fpsLabel(Label("0 fps", 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf")))
	{

		m_mainGameLayer.add(m_playerSprite);
		fpsLabel_ptr = &fpsLabel;

		m_mainGameLayer.add(fpsLabel_ptr);
	}

	// once per second
	void Game::tick() {
		return;
	}
	// 60 times per second
	void Game::update() {
		if (m_window->isKeyPressed(GLFW_KEY_W)) {
			m_player.startAnimation();
			m_player.impulse(maths::vec2(0, 1), 0.05f);
		}
		else if (m_window->isKeyPressed(GLFW_KEY_S)) {
			m_player.startAnimation();
			m_player.impulse(maths::vec2(0, -1), 0.05f);
		}
		if (m_window->isKeyPressed(GLFW_KEY_D)) {
			m_player.startAnimation();
			m_player.impulse(maths::vec2(1, 0), 0.05f);
		}
		else if (m_window->isKeyPressed(GLFW_KEY_A)) {
			m_player.startAnimation();
			m_player.impulse(maths::vec2(-1, 0), 0.05f);
		}
		else {
			//m_player.stopAnimation();
		}

		m_jobSystem.run([this]() {
			m_player.update();
		});
	}
	// unlimited per secondw
	void Game::render() {
		m_mainGameLayer.render();
	}

	void Game::play() {
		int fps = 0;
		std::string labelText;
		m_timer.start();

		while (m_window->close()) {
			unsigned long long deltaTime = m_deltaTimer.count<std::chrono::seconds>();
			//deltaTimer.reset();
			m_deltaTimer.start();

			m_accumulator += deltaTime;
			
			if (m_accumulator >= FIXED_TIMESTEP) {
				m_jobSystem.run([this]() {
					update();
				});
				
				m_accumulator -= FIXED_TIMESTEP;
			}

			m_window->clear();
			render();
			m_window->update();

			fps++;
			if (m_timer.count<std::chrono::seconds>() >= 1) {
				tick();
				labelText = std::to_string(fps) + " fps";
				fpsLabel = Label(labelText, 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), Font("test/fonts/RobotoMono.ttf"));
				fps = 0;
				m_timer.reset();
				m_timer.start();
			}
		}
	}
}