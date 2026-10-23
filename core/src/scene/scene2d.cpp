#include "scene2d.hpp"

namespace heartCore {
	Scene2d::Scene2d(graphics::Window* window)
		: m_window(window),
		m_shader(new graphics::Shader("src/shader/basic.vert", "src/shader/basic.frag")),
		m_graphicLayer(m_shader)
	{}

	void Scene2d::addObject(Entity2d* entity) {
		m_objects.push_back(entity);
	}

	void Scene2d::addObject(
		graphics::StaticSprite* visual,
		maths::vec2* position,
		maths::vec2* size,
		float weight,
		float maxSpeed) 
	{

		m_objects.emplace_back(visual, 
			new physics::ColideBox2d(*visual->position, *visual->size, weight, maxSpeed));
	}
}