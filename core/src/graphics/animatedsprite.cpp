#include "animatedspite.hpp"

namespace heartCore { namespace graphics {
	AnimatedSprite::AnimatedSprite(double x, double y, double width, double height, Texture * texture, int count, std::vector<vec2> coords)
		: StaticSprite(maths::vec2(x, y), maths::vec2(width, height), texture)
	{}

	void AnimatedSprite::nextSprite() {}

	void AnimatedSprite::clearUV() {}

} }