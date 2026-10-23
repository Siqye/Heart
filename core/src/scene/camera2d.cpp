#include "camera2d.hpp"

namespace heartCore {
	Camera2d::Camera2d(maths::vec2 initialPosition = maths::vec2()) 
		: m_position(initialPosition)
	{ }

	void Camera2d::moveTo(maths::vec2 newPosition) {
		m_position = newPosition;
	}
}