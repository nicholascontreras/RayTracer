#pragma once

#include "Vector3D.h"
#include "CameraPixel.h"
#include "Ray.h"
#include "IntersectionInfo.h"

#include <iostream>
#include <vector>

class Camera {
private:
	Vector3D position;
	Vector3D direction;
	Vector3D up;
	unsigned int lensWidth, lensHeight;
	unsigned int pixelsPerUnit;

	CameraPixel* cameraPixels;

	bool mapPointToPixel(Vector3D intersectionLocation, int& pixelX, int& pixelY);

public:
	Camera(unsigned short lensWidth, unsigned short lensHeight, unsigned short pixelsPerUnit) : position(Vector3D(0, 0, 0)), direction(Vector3D(0, 0, 1).normalize()), up(Vector3D(0, 1, 0).normalize()), lensWidth(lensWidth), lensHeight(lensHeight), pixelsPerUnit(pixelsPerUnit) {
		if (!direction.isNormal()) {
			throw std::invalid_argument("Direction vector must be normal!");
		}
		else if (!up.isNormal()) {
			throw std::invalid_argument("Up vector must be normal!");
		}
		
		int numPixels = lensWidth * pixelsPerUnit * lensHeight * pixelsPerUnit;
		cameraPixels = new CameraPixel[numPixels];
	}

	~Camera() {
		delete[] cameraPixels;
	}

	unsigned int getLensWidth();
	unsigned int getLensHeight();
	unsigned int getPixelsPerUnit();
	unsigned int getTotalNumPixels();

	bool rayEntersCamera(Ray ray, IntersectionInfo& intersectionInfo);
	void recordRayHit(Vector3D location, Color color);
	Color* getRenderedImage();
	
};

