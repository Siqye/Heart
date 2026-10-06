#include "levellayer.hpp"
#include "../packetrenderer.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer(Shader* shader) 
		: Layer(shader, new PacketRenderer, maths::mat4::orthographic(0,4,3,0,1,0))
	{}
} }