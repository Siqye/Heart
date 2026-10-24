#pragma once
#include "config.h"
#include "utils/timer.hpp"
#include "graphics/window.hpp"
#include "graphics/sprite.hpp"
#include "graphics/texture.hpp"
#include "graphics/layers/group.hpp"
#include "graphics/layers/levellayer.hpp"
#include "graphics/packetrenderer2d.hpp"
#include "graphics/label.hpp"
#include "graphics/fontmanager.hpp"
#include "audio/sound.hpp"
#include "audio/wavfile.hpp"
#include "audio/speaker.hpp"
#include "physics/physics.hpp"
#include "scene/entity2d.hpp"


using namespace heartCore;
using namespace graphics;
using namespace audio;
using namespace physics;

namespace heartCore {
	class Game {
	private:
		Window* m_window;
		Shader* m_shader;
		LevelLayer m_mainGameLayer;
		ColideManager2d m_physManager;

		float m_playerSpeed;
		std::string* labelText;

		Label fpsLabel;
		Label* fpsLabel_ptr;

		Sprite* m_playerSprite;

		Entity2d m_player;

		Timer m_timer;

		int m_updatesCount;

		// once per second
		void tick();
		// 60 times per second
		void update();
		// unlimited
		void render();
	public:
		Game(int windowWidth, int windowHeight, const char* windowTitle);

		void play();
	};
}