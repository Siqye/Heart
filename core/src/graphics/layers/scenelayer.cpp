#include "scenelayer.hpp"

namespace heartCore { namespace graphics {
	SceneLayer::SceneLayer(Shader* shader)
		: Layer(shader, new PacketRenderer, maths::mat4::perspective(1, 1.2, -40, 40))
	{ }
	SceneLayer::~SceneLayer() {}
} }