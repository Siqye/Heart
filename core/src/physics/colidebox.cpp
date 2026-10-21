#include "colidebox.hpp"

namespace heartCore { namespace physics {
	ColideBox2d::ColideBox2d(maths::vec2 position, maths::vec2 size, float weight) 
		: 
		min(position), 
		max(size), 
		speed(0.0f), 
		direction(maths::vec2(0.0f,0.0f)),
		weight(weight)
	{
		max += min;
	}

	void ColideBox2d::calculateAABB(ColideBox2d* other) {
		if (other->max.x >= this->min.x || other->max.x <= min.x) {
			float intermidX = other->direction.x;
			other->direction.x = this->direction.x;
			this->direction.x = intermidX;
			//this->speed *= 0.85f;
			//other->speed *= 0.85f;
		}

		if (other->min.y >= this->max.y || other->max.y <= min.y) {
			float intermidY = other->direction.y;
			other->direction.y = this->direction.y;
			this->direction.y = intermidY;
			//this->speed *= 0.85f;
			//other->speed *= 0.85f;
		}
	}

	void ColideBox2d::calculateOBB(ColideBox2d* other) {}

	bool ColideBox2d::checkPotential(ColideBox2d* other) {
		// change magic number to variable or contant
		if (this->min.x - 3.0f >= other->max.x || this->max.x + 3.0f >= other->min.x) 
			return true;
		if (this->min.y - 3.0f >= other->max.y || this->max.y + 3.0f >= other->min.y) 
			return true;

		return false;
	}
} }