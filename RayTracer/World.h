#pragma once

#include <vector>
#include "Camera.h"
#include "LightSource.h"
#include "Sphere.h"

class World {
private:
	Camera* camera;
	LightSource* lightSource;
	std::vector<Sphere> spheres;

	void castRay(Ray ray, Sphere* ignore, unsigned int reflectionsRemaining);

public:
	World(Camera* camera, LightSource* lightSource, std::vector<Sphere> spheres) : camera(camera), lightSource(lightSource), spheres(spheres) {}

	~World() {
		delete camera;
		delete lightSource;
		spheres.clear();
	}

	void castRay();

};

