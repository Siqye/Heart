#pragma once
#include "layer.hpp"

namespace heartCore { namespace graphics {
	class LevelLayer : public Layer {
	public:
		LevelLayer() = default;
		~LevelLayer() override = default;

		void add(StaticSprite sprite) override;
		void render(Renderer* renderer) override;
	};
} }