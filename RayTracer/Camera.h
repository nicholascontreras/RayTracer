#pragma once

#include "Vector3D.h"
#include "CameraPixel.h"
#include "Ray.h"
#include "IntersectionInfo.h"
#include "MathUtils.h"

#include <iostream>
#include <vector>

class Camera {
private:
	Vector3D position;
	Vector3D direction;
	Vector3D up;
	unsigned int lensWidth, lensHeight;
	unsigned int pixelsPerUnit;
	unsigned int blurringRadius;

	CameraPixel* cameraPixels;

	bool mapPointToPixel(Vector3D intersectionLocation, int& pixelX, int& pixelY);
	Color* applyBlur(Color image[]);

public:
	Camera(unsigned short lensWidth, unsigned short lensHeight, unsigned short pixelsPerUnit, unsigned short blurringRadius);
	~Camera();

	unsigned int getLensWidth();
	unsigned int getLensHeight();
	unsigned int getPixelsPerUnit();
	unsigned int getTotalNumPixels();

	bool rayEntersCamera(Ray ray, IntersectionInfo& intersectionInfo);
	void recordRayHit(Vector3D location, Color color);
	Color* getRenderedImage();
	
};

