#pragma once
#include <vector>
#include "../renderer.hpp"
#include "../sprite.hpp"
#include "../../maths/maths.hpp"

namespace heartCore { namespace graphics {

	class Group : public Sprite {
	private:
		maths::mat4 m_projectionMatrix;
		std::vector<const Sprite*> m_sprites;
	public:
		Group(const maths::mat4 matrix);
		~Group();

		void add(const Sprite* sprite);
		void submit(Renderer* renderer);
	};

} }