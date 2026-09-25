#pragma once
#include <vector>
#include "../renderer.hpp"
#include "../staticsprite.hpp"
#include "../shader.hpp"

namespace heartCore { namespace graphics {
	class Layer {
	protected:
		Renderer* m_renderer;
		Shader* m_shader;
		maths::mat4 m_projectionMatrix;
		std::vector<StaticSprite*> m_sprites;
	public:
		Layer(Shader* shader, Renderer* renderer, maths::mat4 projectionMatrix);
		~Layer();
		void add(StaticSprite* sprite);
		void render();
	};
} }