#pragma once

#include "Vector3D.h"
#include "Color.h"
#include "Ray.h"

class LightSource {
private:
	Vector3D position;
	Color color;

public:
	LightSource(Vector3D position, Color color) : position(position), color(color) {}

	Ray emitRay();
};

