#pragma once
#include "../maths/maths.hpp"

namespace heartCore {
	namespace physics {
		struct ColideBox2d {
			maths::vec2& min; // position
			maths::vec2& max; // position + size

			float weight;
			maths::vec2 speed;

			float maxSpeed;

			ColideBox2d(maths::vec2 position, maths::vec2 size, float weight, float maxSpeed);

			void calculateAABB(ColideBox2d* other);
			void calculateOBB(ColideBox2d* other);
			bool checkPotential(ColideBox2d* other);
			void impulse(maths::vec2 direction, float power);

			void update();
		};
} }