#pragma once

const double PI = 3.14159265358979323846;

inline double degToRad(double degrees) {
	return degrees * PI / 180;
}

inline double radToDeg(double radians) {
	return radians * 180 / PI;
}
