#include "functions.hpp"
#include <math.h>

namespace heartCore {namespace maths {

	// functions
	float sin(float angle) {
		return sin(angle);
	}

	float cos(float angle) {
		return cos(angle);
	}

	float tan(float angle) {
		return tan(angle);
	}

	float ctg(float angle) {

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

	}

	template <typename Number>
	Number abs(Number num) {
		if (num > 0) return num;
		return num * -1;
	}

	template <typename Number>
	Number pow(Number* number, int power) {

	}

	// utils
	float toRadians(float degrees) {
		return degrees * (M_PI / 180.0f);
	}
	float toAngles(float radians) {
		return radians / (M_PI / 180.0f);
	}

	int ceil(float number) {

	}
	int floor(float number) {

	}
	int round(float number) {

	}

} }