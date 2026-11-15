#include "scenelayer.hpp"

namespace heartCore { namespace graphics {
	SceneLayer::SceneLayer(Shader* shader)
		: Layer(shader, new PacketRenderer, maths::mat4::perspective(90, 20, -40, 40))
	{ }
	SceneLayer::~SceneLayer() {}
} }