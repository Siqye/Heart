#pragma once
#include "config.h"
#include "utils/cxxtimer.hpp"
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
#include "thread/jobsystem.h"
#include "graphics/frameanimation.hpp"
#include "graphics/animatedsprite.hpp"

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
		std::string* labelText;

		Label fpsLabel;
		Label* fpsLabel_ptr;

		AnimatedSprite* m_playerSprite;

		Entity2d m_player;

		Timer m_timer;
		const unsigned long long FIXED_TIMESTEP = 1000 / 60000;
		int m_updatesCount;
		Timer m_deltaTimer;

		threads::JobSystem m_jobSystem;

		unsigned long long m_accumulator;

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