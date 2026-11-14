#include "levellayer.hpp"
#include "../packetrenderer2d.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer(Shader* shader) 
		: Layer(shader, new PacketRenderer, maths::mat4::orthographic(0,40,30,0,10,0))
	{}
} }