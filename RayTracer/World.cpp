#include "World.h"
#include "IntersectionInfo.h"

#include <math.h>

#include <iostream>

Vector3D getReflectionForNormal(Vector3D normal) {
	double pi = 3.14159265358979323846;

	Vector3D reflection;

	while (true) {
		reflection = Vector3D::randomUnitVector();

		if (normal.angleBetween(reflection) < pi / 2) {
			return reflection;
		}
	}
}

void World::castRay(Ray ray, Sphere* ignore, unsigned int reflectionsRemaining) {

	if (reflectionsRemaining == 0) {
		return;
	}

	IntersectionInfo closestIntersection;

	// Find the closest sphere the ray intersects
	for (int i = 0; i < spheres.size(); i++) {
		if (&(spheres[i]) != ignore) {
			IntersectionInfo curIntersection;
			bool anyIntersection = spheres[i].rayIntersects(ray, curIntersection);

			if (anyIntersection) {
				if (curIntersection.t < closestIntersection.t) {
					closestIntersection = curIntersection;
				}
			}
		}
	}

	// Lastly, check to see if the ray enters the camera
	IntersectionInfo cameraIntersectionInfo;
	bool entersCamera = camera->rayEntersCamera(ray, cameraIntersectionInfo);
	if (entersCamera) {
		if (cameraIntersectionInfo.t < closestIntersection.t) {
			// Ray hit the camera before anything else, so tell the camera
			camera->recordRayHit(cameraIntersectionInfo.position, ray.getColor());
			return;
		}
	}

	// Nothing hit, we're done
	if (closestIntersection.t == INFINITY) {
		return;
	}

	Vector3D normal = (closestIntersection.position - closestIntersection.sphere->getPosition()).normalize();
	//Vector3D reflectionAngle = getReflectionForNormal(normal);
	Vector3D reflectionAngle = ray.getDirection() - normal.scale(2 * ray.getDirection().dotProduct(normal));
	Color newColor = ray.getColor().scaleBy(closestIntersection.sphere->getColor());

	Ray reflectedRay = Ray(closestIntersection.position, reflectionAngle, newColor);
	castRay(reflectedRay, closestIntersection.sphere, reflectionsRemaining - 1);
}

void World::castRay() {
	castRay(lightSource->emitRay(), nullptr, 5);
}
