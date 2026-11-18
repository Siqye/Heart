#pragma once
#include "staticsprite.hpp"
#include "frameanimation.hpp"
#include "../utils/cxxtimer.hpp"

namespace heartCore { namespace graphics {
	class AnimatedSprite : public StaticSprite {
	private:
		Animation m_animation;
		Timer m_deltaTimer;
		unsigned long long m_timeStep;
	public:
		AnimatedSprite(double x, double y, double width, double height, std::vector<Texture*> frames);

		void startAnimation() override;
		void stopAnimation() override;

		void update() override;
	};

} }