#pragma once
#include "../maths/maths.hpp"

namespace heartCore {
	namespace physics {
		struct ColideBox2d {
			maths::vec2& min;
			maths::vec2& max;

			float weight;
			float speed;
			maths::vec2 direction;

			ColideBox2d(maths::vec2 position, maths::vec2 size, float weight);

			void calculateAABB(ColideBox2d* other);
			void calculateOBB(ColideBox2d* other);
			bool checkPotential(ColideBox2d* other);

		};
} }