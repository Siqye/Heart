#include "group.hpp"

namespace heartCore { namespace graphics {

	Group::Group(const maths::mat4 matrix) 
		: StaticSprite(), m_projectionMatrix(matrix)
	{}

	Group::~Group() {}
	void Group::submit(Renderer* renderer) {
		renderer->push(m_projectionMatrix);
		for (const StaticSprite* sprite : m_sprites)
			renderer->submit(sprite);
		renderer->pop();

	}
	void Group::add(const StaticSprite* sprite) {
		m_sprites.push_back(sprite);
	}
} }