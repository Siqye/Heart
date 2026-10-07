#pragma once
#include "layer.hpp"
#include "../packetrenderer.hpp"

namespace heartCore { namespace graphics {
	class SceneLayer : public Layer {
		SceneLayer(Shader* shader);
		~SceneLayer();
	};
} }