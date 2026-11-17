#pragma once
#include "staticsprite.hpp"
#include "frameanimation.hpp"

namespace heartCore { namespace graphics {
	class AnimatedSprite : public StaticSprite {
	private:

	public:
		AnimatedSprite(double x, double y, double width, double height, std::vector<Texture*> frames);

		void play();
		void stop();

	};

} }