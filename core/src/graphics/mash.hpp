#pragma once
#include "../maths/maths.hpp"

typedef heartCore::maths::vec3 v3;
typedef heartCore::maths::vec4 v4;

namespace heartCore { namespace graphics {
	class Object3d {
	private:
		v3 m_position;
		v3 m_size;
		v4 m_color;
	public:
		Object3d(v3 position, v3 size, v4 color);

		inline const maths::vec3& getPosition() { return m_position; }
		inline const maths::vec3& getSize() { return m_size; }
		inline const maths::vec4& getColor() { return m_color; }
	};
} }