#pragma once
#include <vector>
#include "../renderer.hpp"
#include "../sprite.hpp"

namespace heartCore { namespace graphics {
	class Layer {
	protected:
		std::vector<Sprite> m_sprites;
	public:
		Layer() {}
		~Layer() {}
		virtual void add(const Sprite& sprite) {}
		virtual void submit(Renderer* renderer) const {}
		virtual void render(Renderer* renderer) {}
	};
} }