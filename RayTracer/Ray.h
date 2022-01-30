#pragma once

#include "Vector3D.h"
#include "Color.h"
#include <stdexcept>

class Ray {

private:
	Vector3D position;
	Vector3D direction;
	Color color;

public:
	Ray(Vector3D position, Vector3D direction, Color color) : position(position), direction(direction), color(color) {
		if (!direction.isNormal()) {
			throw std::invalid_argument("Direction vector must be normal!");
		}
	}

	Vector3D getPosition();
	Vector3D getDirection();
	Color getColor();
};

