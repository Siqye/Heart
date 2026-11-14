#pragma once
#define _USE_MATH_DEFINES

namespace heartCore { namespace maths {
	// functions
	float sin(float angle);
	float cos(float angle);

	float tan(float angle);
	float ctg(float angle);

	float asin(float angle);
	float acos(float angle);
	float atan(float angle);
	float sqrt(float number);

	template <typename Number>
	Number abs(Number num);

	template <typename Number>
	Number pow(Number* number, int power);

	// utils
	float toRadians(float degrees);
	float toAngles(float radians);

	int ceil(float number);
	int floor(float number);
	int round(float number);
} }