#pragma once
#include "layer.hpp"

namespace heartCore { namespace graphics {
	class LevelLayer : public Layer {
	public:
		LevelLayer(Shader* shader);
		~LevelLayer() = default;
	};
} }