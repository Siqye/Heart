#include "layer.hpp"

namespace heartCore {namespace graphics {
	Layer::Layer(Shader* shader, Renderer* renderer, maths::mat4 projectionMatrix)
		: m_shader(shader), m_renderer(renderer), m_projectionMatrix(projectionMatrix)
	{}
	Layer::~Layer() {
//		delete m_renderer;
//		delete m_shader;

//		for (int i = 0; i < m_sprites.size();i++)
//			delete m_sprites[i];
	} /*TODO: FIX LAYER DESCTRUCTOR*/

	void Layer::add(StaticSprite* sprite) {
		m_sprites.push_back(sprite);
	}

	void Layer::render() {
		m_shader->bind();
		m_shader->setUniformMat4f("pr_matrix", m_projectionMatrix);
		m_renderer->begin();

		for (const StaticSprite* sprite : m_sprites)
			sprite->submit(m_renderer);

		m_renderer->end();
		m_renderer->draw();

		m_shader->unbind();
	}
} }