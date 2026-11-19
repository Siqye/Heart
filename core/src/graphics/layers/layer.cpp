#include "layer.hpp"
#include <stdexcept>

namespace heartCore {namespace graphics {
	Layer::Layer(std::shared_ptr<Shader> shader, std::shared_ptr<Renderer2D> renderer, maths::mat4 projectionMatrix)
		: m_shader(shader), m_renderer(renderer), m_projectionMatrix(projectionMatrix)
	{
		if (!m_shader || !m_renderer)
			throw std::invalid_argument("Layer requires a shader and renderer");
		shader->bind();
		int textureIDs[] = {
			 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10,11,12,13,14,15,16,17,18,19,
			20,21,22,23,24,25,26,27,28,29,
			30,31
		};
		
		shader->setUniform1iv("textures", 32, textureIDs);
	}
	Layer::~Layer() {
		//for (int i = 0; i < m_sprites.size();i++)
		//	delete m_sprites[i];

		//delete m_renderer;
		//delete m_shader;
	} /*TODO: FIX LAYER DESCTRUCTOR*/

	void Layer::add(std::shared_ptr<StaticSprite> sprite) {
		if (sprite)
			m_sprites.push_back(std::move(sprite));
	}

	void Layer::render() {
		if (!m_shader || !m_renderer)
			return;
		m_shader->bind();
		m_shader->setUniformMat4f("projection", m_projectionMatrix);
		m_renderer->begin();

		for (const auto& sprite : m_sprites)
			sprite->submit(m_renderer.get());

		m_renderer->end();
		m_renderer->draw();

		m_shader->unbind();
	}
} }