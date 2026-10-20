#include "functions.hpp"
#include <math.h>

namespace heartCore {namespace maths {

	static float sinTable[360];

	// functions
	float sin(float degrees) {
		return sinf(toRadians(degrees));
	}

	float cos(float degrees) {
		return sin(toRadians(degrees) + (M_PI / 4)); // same like sin but offset 90 degreeses
	}

	float tan(float degrees) {
		return tanf(toRadians(degrees));
	}

	float ctg(float degrees) {
		return tan(toRadians(degrees) + (M_PI / 4)); // same tan but also offset 90 degreeses
	}

	float asin(float angle) {
		return 1 / sin(angle);
	}
	float acos(float angle) {
		return 1 / cos(angle);
	}
	float atan(float angle) {
		return 1 / tan(angle);
	}
	float sqrt(float number) {
		if (number < 0.0f)
			return -1.0f;

		if (number == 0.0f)
			return 0.0f;

		float low = 0.0f;
		float high = number > 1.0f ? number : 1.0f;
		float mid;

		for (int i = 0; i < 32; i++) {
			mid = (low + high) / 2.0f;
			float square = mid * mid;

			if (square > number)
				high = mid;
			else
				low = mid;
		}

		return (low + high) / 2.0f;
	}

	template <typename Number>
	Number abs(Number num) {
		if (num >= 0) return num;
		return num * -1;
	}

	template <typename Number>
	Number pow(Number number, int power) {
		Number result;
		for (int i = 0;i <= power;i++) {
			result *= number;
		}
		return result;
	}

	// utils
	float toRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}
	float toAngles(float radians) {
		return radians / (M_PI / 180.0f);
	}

	// rounding
	int ceil(float number) {
		return (int)number + 1;
	}
	int floor(float number) {
		return (int)number;
	}
	int round(float number) {
		if ((int)(number * 10) % 10 > 5) return (int)number + 1;
		return (int)number;
	}

} }