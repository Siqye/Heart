#pragma once
#include "../maths/maths.hpp"

namespace heartCore {
	class Camera2d {
	private:
		maths::vec2 m_position;
	public:
		Camera2d();
		Camera2d(maths::vec2 initalPosition);

		void moveTo(maths::vec2 newPosition);
	};
}