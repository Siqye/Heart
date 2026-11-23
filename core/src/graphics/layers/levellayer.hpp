#pragma once
#include "layer.hpp"

namespace heartCore { namespace graphics {
	using namespace API;
	class LevelLayer : public Layer {
	public:
		LevelLayer(std::shared_ptr<Shader> shader);
		~LevelLayer() = default;
	};
} }