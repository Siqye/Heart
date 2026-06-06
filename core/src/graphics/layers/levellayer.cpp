#include "levellayer.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer() : Layer() {}
	LevelLayer::~LevelLayer() {}

	void LevelLayer::add(const Sprite& sprite) {
		m_sprites.push_back(sprite);
	}

	void LevelLayer::submit(Renderer* renderer) const {
		for (Sprite sprite : m_sprites)
			sprite.submit(renderer);
	}

	void LevelLayer::render(Renderer* renderer) {
		renderer->begin();
		for (int i = 0; i < m_sprites.size(); i++)
			m_sprites[i].submit(renderer);
		renderer->end();
		renderer->draw();
	}
} }