#include "Camera.h"

#include "Ray.h"

#include <algorithm>
#include <stdexcept>

unsigned int Camera::getLensWidth() {
	return lensWidth;
}

unsigned int Camera::getLensHeight() {
	return lensHeight;
}

unsigned int Camera::getPixelsPerUnit() {
	return pixelsPerUnit;
}

unsigned int Camera::getTotalNumPixels() {
	return lensWidth * pixelsPerUnit * lensHeight * pixelsPerUnit;
}

bool Camera::mapPointToPixel(Vector3D intersectionLocation, int& pixelX, int& pixelY) {	
	Vector3D cameraPlaneXAxis = up.crossProduct(direction);

	double projectedX = (intersectionLocation - position).dotProduct(cameraPlaneXAxis);
	double projectedY = (intersectionLocation - position).dotProduct(direction.crossProduct(cameraPlaneXAxis));

	pixelX = round(projectedX * pixelsPerUnit) + (lensWidth * pixelsPerUnit / 2);
	pixelY = round(projectedY * pixelsPerUnit) + (lensHeight * pixelsPerUnit / 2);;

	// Return whether or not the intersection location is actually on the camera lens
	return pixelX >= 0 && pixelX < lensWidth * pixelsPerUnit && pixelY >= 0 && pixelY < lensHeight * pixelsPerUnit;
}

bool Camera::rayEntersCamera(Ray ray, IntersectionInfo& intersectionInfo) {
	double denom = direction.dotProduct(ray.getDirection());

	// Ensure the ray is entering the plane at some sort of appreciable angle
	if (denom > -1e-6) {
		return false;
	}

	// Ensure the ray is entering through the front of the camera
	if (direction.angleBetween(ray.getDirection()) < PI / 2) {
		return false;
	}

	// Enforce 90 degree FOV
	if (ray.getDirection().angleBetween(direction.scale(-1)) > PI / 4) {
		return false;
	}

	Vector3D p0l0 = position - ray.getPosition();
	double t = p0l0.dotProduct(direction) / denom;
	if (t >= 0) {
		Vector3D intersectionLocation = ray.getPosition() + (ray.getDirection().scale(t));

		int pixelX, pixelY;
		if (mapPointToPixel(intersectionLocation, pixelX, pixelY)) {
			intersectionInfo.t = t;
			intersectionInfo.sphere = nullptr;
			intersectionInfo.position = intersectionLocation;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
 }

void Camera::recordRayHit(Vector3D location, Color color) {
	int pixelX, pixelY;
	if (!mapPointToPixel(location, pixelX, pixelY)) {
		throw std::invalid_argument("Location given is not on the camera lens!");
	}

	int pixelIndex = (pixelY * (lensWidth * pixelsPerUnit)) + pixelX;
	cameraPixels[pixelIndex].addIncomingRay(color);
}

Color* Camera::getRenderedImage() {
	unsigned int maxNumRaysReceived = 0;
	for (int i = 0; i < getTotalNumPixels(); i++) {
		maxNumRaysReceived = std::max(maxNumRaysReceived, cameraPixels[i].getNumRaysReceived());
	}

	double brightnessScalingFactor = 1.0 / maxNumRaysReceived;

	Color* image = new Color[getTotalNumPixels()];
	for (int i = 0; i < getTotalNumPixels(); i++) {
		Color brightnessScaledColor = cameraPixels[i].getAverageColor();
		brightnessScaledColor = brightnessScaledColor.scale(brightnessScalingFactor);
		brightnessScaledColor = brightnessScaledColor.scale(cameraPixels[i].getNumRaysReceived());
		image[i] = brightnessScaledColor;
	}

	return image;
}
