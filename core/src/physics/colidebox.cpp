#include "colidebox.hpp"

namespace heartCore { namespace physics {
	ColideBox2d::ColideBox2d(maths::vec2* position, maths::vec2* size, float weight, float maxSpeed = 0.0f) 
		: 
		min(position), 
		max(size), 
		speed(maths::vec2(0.0f, 0.0f)),
		weight(weight),
		maxSpeed(maxSpeed)
	{
		*max += *min;
	}

	void ColideBox2d::calculateAABB(ColideBox2d* other) {
		if (other->max->x >= this->min->x || other->max->x <= this->min->x) {
			float intermidX = other->speed.x;
			other->speed.x = this->speed.x;
			this->speed.x = intermidX;
		}

		if (other->min->y >= this->max->y || other->max->y <= this->min->y) {
			float intermidY = other->speed.y;
			other->speed.y = this->speed.y;
			this->speed.y = intermidY;
		}
	}

	void ColideBox2d::calculateOBB(ColideBox2d* other) {}

	bool ColideBox2d::checkPotential(ColideBox2d* other) {
		// change magic number to variable or constant
		if (this->min->x - 3.0f >= other->max->x || this->max->x + 3.0f >= other->min->x)
			return true;
		if (this->min->y - 3.0f >= other->max->y || this->max->y + 3.0f >= other->min->y)
			return true;

		return false;
	}

	void ColideBox2d::impulse(maths::vec2 direction, float power) {
		direction.x *= power;
		direction.y *= power;

		if (direction.x + this->speed.x >= maxSpeed) {
			direction.x = maxSpeed;
			this->speed.x = 0.0f;
		}

		if (direction.y + this->speed.y >= maxSpeed) {
			direction.y = maxSpeed;
			this->speed.y = 0.0f;
		}
		this->speed += direction;
	}

	void ColideBox2d::update() {
		*this->min += speed;
		*this->max += speed;

		//	        коеф времени  плотность среды         квадрат скорости	    лобовое сопротивление
		this->speed.x += 0.008f * MEDIUM_DENSITY_FLOAT * (speed.x * speed.x); // теперь всегда 1
		this->speed.y += 0.008f * MEDIUM_DENSITY_FLOAT * (speed.y * speed.y);
	}

} }