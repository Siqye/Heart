#include "mash.hpp"

namespace heartCore { namespace graphics {
	Object3d::Object3d(v3 position, v3 size, v4 color) 
		: m_position(position), m_size(size), m_color(color)
	{}
} }