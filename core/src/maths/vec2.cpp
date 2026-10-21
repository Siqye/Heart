#include "vec2.hpp"


namespace heartCore {
	namespace maths {
		vec2::vec2() {
			x = 0.0f;
			y = 0.0f;
		}

		vec2::vec2(const float& x, const float& y) {
			this->x = x;
			this->y = y;
		}

		vec2& vec2::add(const vec2& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		vec2& vec2::substract(const vec2& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		vec2& vec2::multiply(const vec2& other) {
			this->x *= other.x;
			this->y *= other.y;
			return *this;
		}

		vec2& vec2::divide(const vec2& other) {
			this->x /= other.x;
			this->y /= other.y;
			return *this;
		}

		void vec2::normalize() {
			float normalization = sqrt(
				x * x +
				y * y);

			if (normalization == 0.0f)
				return;

			x /= normalization;
			y /= normalization;
		}

		vec2& vec2::normalized(vec2& vector) {
			float normalization = sqrt(
				vector.x * vector.x +
				vector.y * vector.y);

			if (normalization == 0) return vector;

			vector.x /= normalization;
			vector.y /= normalization;

			return vector;
		}


		vec2 operator+(vec2 left, const vec2& right) {
			return left.add(right);
		}
		vec2 operator-(vec2 left, const vec2& right) {
			return left.substract(right);
		}
		vec2 operator*(vec2 left, const vec2& right) {
			return left.multiply(right);
		}
		vec2 operator/(vec2 left, const vec2& right) {
			return left.divide(right);
		}

		vec2& vec2::operator+=(const vec2& other) {
			return add(other);
		}
		vec2& vec2::operator-=(const vec2& other) {
			return substract(other);
		}
		vec2& vec2::operator*=(const vec2& other) {
			return multiply(other);
		}
		vec2& vec2::operator/=(const vec2& other) {
			return divide(other);
		}

		std::ostream& operator <<(std::ostream& stream, const vec2& vector)
		{
			stream << "vec2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}
	}
}