#include "vec3.hpp"
#include "maths.hpp"

namespace heartCore {
	namespace maths {
		vec3::vec3() {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		vec3::vec3(const float& x, const float& y, const float& z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3& vec3::add(const vec3& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			return *this;
		}

		vec3& vec3::substract(const vec3& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			return *this;
		}

		vec3& vec3::multiply(const vec3& other) {
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			return *this;
		}

		vec3& vec3::divide(const vec3& other) {
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			return *this;
		}

		void vec3::normalize() {
			float normalization = sqrt(
				x * x + 
				y * y + 
				z * z);
	
			if (normalization == 0.0f) 
				return;

			x /= normalization;
			y /= normalization;
			z /= normalization;
		}

		vec3& vec3::normalized(vec3& vector) {
			float normalization = sqrt(
				vector.x * vector.x + 
				vector.y * vector.y + 
				vector.z * vector.z);

			if (normalization == 0) return vector;

			vector.x /= normalization;
			vector.y /= normalization;
			vector.z /= normalization;

			return vector;
		}


		vec3 operator+(vec3 left, const vec3& right) {
			return left.add(right);
		}
		vec3 operator-(vec3 left, const vec3& right) {
			return left.substract(right);
		}
		vec3 operator*(vec3 left, const vec3& right) {
			return left.multiply(right);
		}
		vec3 operator/(vec3 left, const vec3& right) {
			return left.divide(right);
		}

		vec3& vec3::operator+=(const vec3& other) {
			return add(other);
		}
		vec3& vec3::operator-=(const vec3& other) {
			return substract(other);
		}
		vec3& vec3::operator*=(const vec3& other) {
			return multiply(other);
		}
		vec3& vec3::operator/=(const vec3& other) {
			return divide(other);
		}

		std::ostream& operator <<(std::ostream& stream, const vec3& vector)
		{
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}
	}
}