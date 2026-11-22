#include "test.hpp"
#include "logger/logger.hpp"

namespace heartCore {
	Game::Game(int windowWidth, int windowHeight, const char* windowTitle)
		:
		m_window(std::make_unique<Window>(windowWidth, windowHeight, windowTitle)),
		m_shader(std::make_shared<Shader>("src/shader/basic.vert", "src/shader/basic.frag")),
		m_mainGameLayer(m_shader),
		m_physManager(),
		m_playerSprite(std::make_shared<Sprite>(
				25.0, 10.0, 5.0, 5.0,
				std::make_shared<Texture>("test/test1.png")
		)),
		m_huesosSprite(std::make_shared<Sprite>(10.0, 10.0, 5.0, 5.0, std::make_shared<Texture>("test/test5.png"))),
		m_huesosBox(std::make_shared<ColideBox2d>(m_huesosSprite->position, m_huesosSprite->size, 10, 2.0f)),
		m_playerBox(std::make_shared<ColideBox2d>(m_playerSprite->position, m_playerSprite->size, 10, 2.0f)),
		m_player(m_playerSprite, m_playerBox),
		fpsLabel(std::make_shared<Label>("0 fps", 10, 0.1f, 29.0f, maths::vec4(1, 1, 1, 1), "RobotoMono.ttf")),
		upsLabel(std::make_shared<Label>("0 ups", 10, 0.1f, 28.0f, maths::vec4(1, 1, 1, 1), "RobotoMono.ttf")),
		m_huesos(m_huesosSprite, m_huesosBox)
	{

		auto anim = std::make_shared<AtlasAnimation>(std::vector<maths::vec2>{
			maths::vec2(0, 0), maths::vec2(32, 0), maths::vec2(64, 0)
		},
			std::make_shared<Texture>("test/human_walk_animation_test.png"), 32, 32, 200, true);

		m_player.setAnimation(EntityState::WALK, anim);
		m_mainGameLayer.add(m_playerSprite);
		m_mainGameLayer.add(fpsLabel);
		m_mainGameLayer.add(m_huesosSprite);
		m_mainGameLayer.add(upsLabel);

		LOG_INFO("Engine succefuly started!");
	}

	// once per second
	void Game::tick() {
		return;
	}
	// 60 times per second
	void Game::update() {
		ups++;
		

		if (m_window->isKeyPressed(GLFW_KEY_W)) {
			m_player.impulse(maths::vec2(0, 1), 0.05f);
		}
		else if (m_window->isKeyPressed(GLFW_KEY_S)) {
			m_player.impulse(maths::vec2(0, -1), 0.05f);
		}
		if (m_window->isKeyPressed(GLFW_KEY_D)) {
			m_player.impulse(maths::vec2(1, 0), 0.05f);
		}
		else if (m_window->isKeyPressed(GLFW_KEY_A)) {
			m_player.impulse(maths::vec2(-1, 0), 0.05f);
		}
		
		if (m_window->isKeyPressed(GLFW_KEY_W) ||
			m_window->isKeyPressed(GLFW_KEY_S) ||
			m_window->isKeyPressed(GLFW_KEY_D) ||
			m_window->isKeyPressed(GLFW_KEY_A)) {
			if (m_player.getState() != EntityState::WALK)
				m_player.setState(EntityState::WALK);
		} else {
			m_player.setState(EntityState::IDLE);
		}

		m_jobSystem.run([this]() {
			m_player.update();
			m_playerBox->calculateAABB(*m_huesosBox);
			m_huesos.update();
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
			//deltaTimer.reset();
			m_deltaTimer.start();
			
			if (m_deltaTimer.count<std::chrono::microseconds>() >= FIXED_TIMESTEP) {
				m_jobSystem.run([this]() {
					update();
				});

				m_deltaTimer.reset();
			}

			m_window->clear();
			render();
			m_window->update();

			fps++;
			if (m_timer.count<std::chrono::seconds>() >= 1) {
				tick();
				labelText = std::to_string(fps) + " fps";
				fpsLabel->setText(labelText);
				fps = 0;
				upsLabel->setText(std::to_string(ups) + " ups");
				ups = 0;
				m_timer.reset();
				m_timer.start();
			}
		}
	}
}