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
		AnimatedSprite(double x, double y, double width, double height, std::vector<std::shared_ptr<Texture>> frames);

		void startAnimation() override;
		void stopAnimation() override;

		void update() override;

		inline const bool& isPlaying() { return m_animation.isPlaying(); }
	};

} }