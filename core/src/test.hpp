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
#include <memory>

using namespace heartCore;
using namespace graphics;
using namespace audio;
using namespace physics;

namespace heartCore {
	class Game {
	private:
		std::unique_ptr<Window> m_window;
		std::shared_ptr<Shader> m_shader;
		LevelLayer m_mainGameLayer;
		ColideManager2d m_physManager;
		std::shared_ptr<Label> fpsLabel;

		std::shared_ptr<AnimatedSprite> m_playerSprite;
		std::shared_ptr<Sprite> m_huesosSprite;

		Entity2d m_player;
		Entity2d m_huesos;

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