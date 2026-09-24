#include "levellayer.hpp"

namespace heartCore { namespace graphics {
	//LevelLayer::LevelLayer() : Layer() {}
	//LevelLayer::~LevelLayer() {}

	void LevelLayer::add(StaticSprite sprite) {
		m_sprites.push_back(sprite);
	}

	void LevelLayer::render(Renderer* renderer) {
		renderer->begin();
		for (StaticSprite sprite : m_sprites)
			sprite.submit(renderer);

		renderer->end();
		renderer->draw();
	}
} }