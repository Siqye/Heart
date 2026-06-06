#pragma once
#include "layer.hpp"

namespace heartCore { namespace graphics {
	class LevelLayer : public Layer {
	public:
		LevelLayer();
		~LevelLayer();

		void add(const Sprite& sprite) override;
		void submit(Renderer* renderer) const override;
		void render(Renderer* renderer) override;
	};
} }