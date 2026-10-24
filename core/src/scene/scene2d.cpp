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
}