#include "object3d.hpp"

namespace heartCore {namespace graphics {
	Object3d::Object3d(maths::vec3 position, maths::vec3 size, maths::vec4 color)
		: m_position(position), m_size(size), m_color(color)
	{}

	Object3d::~Object3d() {}
} }