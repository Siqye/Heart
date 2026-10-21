#include "vec4.hpp"

namespace heartCore {
	namespace maths {
		/*vec4::vec4() {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}*/

		vec4::vec4(const float& x, const float& y, const float& z, const float& w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4& vec4::add(const vec4& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;
			return *this;
		}

		vec4& vec4::substract(const vec4& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;
			return *this;
		}

		vec4& vec4::multiply(const vec4& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;
			return *this;
		}

		vec4& vec4::divide(const vec4& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;
			return *this;
		}

		void vec4::normalize() {
			float normalization = sqrt(
				x * x +
				y * y +
				z * z +
				w * w);

			if (normalization == 0.0f)
				return;

			x /= normalization;
			y /= normalization;
			z /= normalization;
			w /= normalization;
		}

		vec4& vec4::normalized(vec4& vector) {
			float normalization = sqrt(
				vector.x * vector.x +
				vector.y * vector.y +
				vector.z * vector.z +
				vector.w * vector.w);

			if (normalization == 0) return vector;

			vector.x /= normalization;
			vector.y /= normalization;
			vector.z /= normalization;
			vector.w /= normalization;

			return vector;
		}


		vec4 operator+(vec4 left, const vec4& right) {
			return left.add(right);
		}
		vec4 operator-(vec4 left, const vec4& right) {
			return left.substract(right);
		}
		vec4 operator*(vec4 left, const vec4& right) {
			return left.multiply(right);
		}
		vec4 operator/(vec4 left, const vec4& right) {
			return left.divide(right);
		}

		vec4& vec4::operator+=(const vec4& other) {
			return add(other);
		}
		vec4& vec4::operator-=(const vec4& other) {
			return substract(other);
		}
		vec4& vec4::operator*=(const vec4& other) {
			return multiply(other);
		}
		vec4& vec4::operator/=(const vec4& other) {
			return divide(other);
		}

		std::ostream& operator <<(std::ostream& stream, const vec4& vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}
	}
}