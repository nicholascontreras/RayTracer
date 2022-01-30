#pragma once

#include "Sphere.h"

struct IntersectionInfo {
	double t;
	Sphere* sphere;
	Vector3D position;

public:
	IntersectionInfo() : t(INFINITY), sphere(nullptr), position(Vector3D()) {}
};
