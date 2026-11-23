#include "levellayer.hpp"
#include "../API/packetrenderer2d.hpp"

namespace heartCore { namespace graphics {
	using namespace API;
	LevelLayer::LevelLayer(std::shared_ptr<Shader> shader)
		: Layer(shader, std::make_shared<PacketRenderer>(), maths::mat4::orthographic(0,40,30,0,10,0))
	{}
} }