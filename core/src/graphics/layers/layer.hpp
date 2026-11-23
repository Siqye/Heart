#pragma once
#include <vector>
#include "../API/renderer2d.hpp"
#include "../API/staticsprite.hpp"
#include "../API/shader.hpp"
#include <memory>

namespace heartCore { namespace graphics {
	using namespace API;
	class Layer {
	protected:
		std::shared_ptr<Renderer2D> m_renderer;
		std::shared_ptr<Shader> m_shader;
		maths::mat4 m_projectionMatrix;
		std::vector<std::shared_ptr<StaticSprite>> m_sprites;
	public:
		Layer(std::shared_ptr<Shader> shader, std::shared_ptr<Renderer2D> renderer, maths::mat4 projectionMatrix);
		~Layer();
		void add(std::shared_ptr<StaticSprite> sprite);
		void render();
	};
} }