#pragma once
#include <vector>
#include "../renderer.hpp"
#include "../staticsprite.hpp"

namespace heartCore { namespace graphics {
	class Layer {
	protected:
		std::vector<StaticSprite*> m_sprites;
	public:
		virtual ~Layer() = default;
		virtual void add(StaticSprite* sprite) {}
		virtual void render(Renderer* renderer) {}

		virtual void pop() { m_sprites.pop_back(); }
	};
} }