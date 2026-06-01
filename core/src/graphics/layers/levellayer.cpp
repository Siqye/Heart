#include "levellayer.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer() : Layer() {}
	LevelLayer::~LevelLayer() {}

	void LevelLayer::add(const Sprite& sprite) {
		m_sprites.push_back(sprite);
	}

	void LevelLayer::submit(Renderer* renderer) const {
		for (Sprite sprite : m_sprites)
			renderer->submit(&sprite);//sprite.submit(renderer);
	}
} }