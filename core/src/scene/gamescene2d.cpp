#include "gamescene2d.hpp"

namespace heartCore {
	GameScene2d::GameScene2d() : Scene2d()
	{
		m_graphicLayer.add(m_player->getVisual());
	}

	void GameScene2d::render() {
		m_graphicLayer.render();
	}
	
	void GameScene2d::update() {
		
	}
	
	void GameScene2d::tick() {

	}
}