#include "colidebox.hpp"
#include <cmath>

namespace heartCore { namespace physics {
	ColideBox2d::ColideBox2d(maths::vec2& position, maths::vec2& size, float weight, float maxSpeed)
		: 
		min(position), 
		size(size),
		max(position + size),
		speed(maths::vec2(0.0f, 0.0f)),
		weight(weight),
		maxSpeed(maxSpeed)
	{}

	void ColideBox2d::calculateAABB(ColideBox2d& other) {
		if (this->min.x < other.max.x && this->max.x > other.min.x &&
			this->min.y < other.max.y && this->max.y > other.min.y) {

			float tempX = other.speed.x;
			other.speed.x = this->speed.x;
			this->speed.x = tempX;

			float tempY = other.speed.y;
			other.speed.y = this->speed.y;
			this->speed.y = tempY;
		}
	}

	void ColideBox2d::calculateOBB(ColideBox2d& other) {}

	bool ColideBox2d::checkPotential(ColideBox2d& other) {
		// change magic number to variable or constant
		if ((this->min.x - POTENTIAL_LENGHT <= other.max.x && this->max.x + POTENTIAL_LENGHT >= other.min.x) &&
			(this->min.y - POTENTIAL_LENGHT <= other.max.y && this->max.y + POTENTIAL_LENGHT >= other.min.y))
			return true;

		return false;
	}

	void ColideBox2d::impulse(maths::vec2 direction, float power) {
		direction.x *= power;
		direction.y *= power;

		// impulse to speed
		this->speed.x += direction.x;
		this->speed.y += direction.y;

		// speed limit
		float speedMagnitude = std::sqrt(this->speed.x * this->speed.x + this->speed.y * this->speed.y);
		// change from magic to constant
		if (speedMagnitude <= 0.01f) {
			this->speed.x = 0.0f;
			this->speed.y = 0.0f;
			return;
		}

		if (speedMagnitude >= maxSpeed && maxSpeed > 0.0f) {
			// normalazing speed to max value
			float scale = maxSpeed / speedMagnitude;
			this->speed.x *= scale;
			this->speed.y *= scale;
		}
	}

	void ColideBox2d::update() {
		this->min += speed;

		this->max = min + size;

		this->speed.x -= MEDIUM_DENSITY_FLOAT * speed.x * std::abs(speed.x);
		this->speed.y -= MEDIUM_DENSITY_FLOAT * speed.y * std::abs(speed.y);
	}

} }
