#include "levellayer.hpp"
#include "../renderer2d.hpp"

namespace heartCore { namespace graphics {
	LevelLayer::LevelLayer(Shader* shader) 
		: Layer(shader, new Renderer2d, maths::mat4::orthographic(0,4,3,0,1,0))
	{}
} }