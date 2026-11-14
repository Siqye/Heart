#pragma once
#include "../maths/maths.hpp"

namespace heartCore { namespace graphics {
	struct UnitData3d {
		maths::vec3 vertex;
		unsigned int color;
	};
	
	class Object3d {
	private:
		maths::vec3 m_position;
		maths::vec3 m_size;
		maths::vec4 m_color;
	public:
		Object3d(maths::vec3 position, maths::vec3 size, maths::vec4 color);
		~Object3d();

		const maths::vec3& getPosition() { return m_position; }
		const maths::vec3& getSize() { return m_size; }
		const maths::vec4& getColor() { return m_color; }
	};
} }