#pragma once
#include <vector>
#include "../renderer.hpp"
#include "../staticsprite.hpp"

namespace heartCore { namespace graphics {
	class Layer {
	protected:
		std::vector<StaticSprite> m_sprites;
	public:
		Layer() {}
		~Layer() {}
		virtual void add(const StaticSprite& sprite) {}
		virtual void submit(Renderer* renderer) const {}
		virtual void render(Renderer* renderer) {}
	};
} }