#pragma once
#include "layer.hpp"
#include "../packetrenderer.hpp"

namespace heartCore { namespace graphics {
	class SceneLayer : public Layer {
	public:
		SceneLayer(Shader* shader);
		~SceneLayer();
	};
} }