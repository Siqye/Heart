#include "levellayer.hpp"

namespace heartCore { namespace graphics {
	//LevelLayer::LevelLayer() : Layer() {}
	//LevelLayer::~LevelLayer() {}

	void LevelLayer::add(std::unique_ptr<StaticSprite> sprite) {
		m_sprites.push_back(std::move(sprite));
	}

	void LevelLayer::render(Renderer* renderer) {
		renderer->begin();
		for (int i = 0; i < m_sprites.size(); i++)
			m_sprites[i]->submit(renderer);

		renderer->end();
		renderer->draw();
	}
} }