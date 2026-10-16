#pragma once
#include <vector>
#include "../renderer2d.hpp"
#include "../staticsprite.hpp"
#include "../../maths/maths.hpp"

namespace heartCore { namespace graphics {

	class Group : public StaticSprite {
	private:
		maths::mat4 m_projectionMatrix;
		std::vector<const StaticSprite*> m_sprites;
	public:
		Group(const maths::mat4 matrix);
		~Group();

		void add(const StaticSprite* sprite);
		void submit(Renderer2D* renderer);
	};

} }