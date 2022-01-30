#include "LightSource.h"

Ray LightSource::emitRay() {
	Vector3D vector;
	while (true) {
		vector = Vector3D::randomUnitVector();

		if (vector.getZ() > 0) {
			break;
		}
	}
	return Ray(position, vector, color);
}
