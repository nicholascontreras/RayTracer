#pragma once

#include "Vector3D.h"
#include "Ray.h"
#include <stdexcept>

struct IntersectionInfo;

class Sphere {

private:
	Vector3D position;
	double radius;
	Color color;

public:
	Sphere(Vector3D position, double radius, Color color) : position(position), radius(radius), color(color) {
		if (radius <= 0) {
			throw std::invalid_argument("Radius must be greater than zero!");
		}
	}

	Vector3D getPosition();
	Color getColor();

	bool rayIntersects(Ray ray, IntersectionInfo& intersectionInfo);
};

