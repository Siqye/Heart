#include "levellayer.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer() : Layer() {}
	LevelLayer::~LevelLayer() {}

	void LevelLayer::add(const StaticSprite& sprite) {
		m_sprites.push_back(sprite);
	}

	void LevelLayer::submit(Renderer* renderer) const {
		for (int i = 0; i < m_sprites.size();i++)
			m_sprites[i].submit(renderer);
	}

	void LevelLayer::render(Renderer* renderer) {
		renderer->begin();
		for (int i = 0; i < m_sprites.size(); i++)
			m_sprites[i].submit(renderer);

		renderer->submitText("heart engine",maths::vec3(0,0,0),maths::vec4(1,1,0,1));

		renderer->end();
		renderer->draw();
	}
} }