#pragma once
#include "layer.hpp"
#include "../API/packetrenderer2d.hpp"

namespace heartCore { namespace graphics {
	using namespace API;
	class SceneLayer : public Layer {
	public:
		SceneLayer(Shader* shader);
		~SceneLayer();
	};
} }