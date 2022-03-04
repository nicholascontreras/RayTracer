#include "Camera.h"

#include "Ray.h"

#include <algorithm>
#include <stdexcept>

Camera::Camera(unsigned short lensWidth, unsigned short lensHeight, unsigned short pixelsPerUnit, unsigned short blurringRadius) : 
	position(Vector3D(0, 0, 0)), 
	direction(Vector3D(0, 0, 1).normalize()), 
	up(Vector3D(0, 1, 0).normalize()), 
	lensWidth(lensWidth), 
	lensHeight(lensHeight), 
	pixelsPerUnit(pixelsPerUnit), 
	blurringRadius(blurringRadius) {

	if (!direction.isNormal()) {
		throw std::invalid_argument("Direction vector must be normal!");
	}
	else if (!up.isNormal()) {
		throw std::invalid_argument("Up vector must be normal!");
	}

	int numPixels = lensWidth * pixelsPerUnit * lensHeight * pixelsPerUnit;
	cameraPixels = new CameraPixel[numPixels];
}

Camera::~Camera() {
	delete[] cameraPixels;
}

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

	pixelX = (int) round(projectedX * pixelsPerUnit) + (lensWidth * pixelsPerUnit / 2);
	pixelY = (int) round(projectedY * pixelsPerUnit) + (lensHeight * pixelsPerUnit / 2);

	// Return whether or not the intersection location is actually on the camera lens
	return pixelX >= 0 && pixelX < (int) (lensWidth * pixelsPerUnit) && pixelY >= 0 && pixelY < (int) (lensHeight * pixelsPerUnit);
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
	for (unsigned int i = 0; i < getTotalNumPixels(); i++) {
		maxNumRaysReceived = std::max(maxNumRaysReceived, cameraPixels[i].getNumRaysReceived());
	}

	double brightnessScalingFactor = 1.0 / maxNumRaysReceived;

	unsigned int totalNumPixels = getTotalNumPixels();
	Color* image = new Color[totalNumPixels];
	for (unsigned int i = 0; i < totalNumPixels; i++) {
		Color brightnessScaledColor = cameraPixels[i].getAverageColor();
		brightnessScaledColor = brightnessScaledColor.scale(brightnessScalingFactor);
		brightnessScaledColor = brightnessScaledColor.scale(cameraPixels[i].getNumRaysReceived());
		image[i] = brightnessScaledColor;
	}

	// Apply blurring if it's been enabled
	if (blurringRadius) {
		std::cout << "Applying box blur..." << std::endl;
		Color* blurredImage = applyBlur(image);
		delete[] image;
		image = blurredImage;
		std::cout << "Box blur complete" << std::endl;
	}

	return image;
}

Color* Camera::applyBlur(Color image[]) {

	Color* blurredImage = new Color[getTotalNumPixels()];

	unsigned int numPixelsVert = lensHeight * pixelsPerUnit;
	unsigned int numPixelsHorz = lensWidth * pixelsPerUnit;

	for (unsigned int row = 0; row < numPixelsVert; row++) {
		for (unsigned int col = 0; col < numPixelsHorz; col++) {
			unsigned int index = (row * numPixelsHorz) + col;
			double totalR = 0, totalG = 0, totalB = 0;
			unsigned short numSamples = 0;

			for (unsigned int sampleRow = row - blurringRadius; sampleRow <= row + blurringRadius; sampleRow++) {
				for (unsigned int sampleCol = col - blurringRadius; sampleCol <= col + blurringRadius; sampleCol++) {
					if (sampleRow >= 0 && sampleRow < numPixelsVert) {
						if (sampleCol >= 0 && sampleCol < numPixelsHorz) {
							int sampleIndex = (sampleRow * numPixelsHorz) + sampleCol;
							totalR += image[sampleIndex].getRed();
							totalG += image[sampleIndex].getGreen();
							totalB += image[sampleIndex].getBlue();
							numSamples++;
						}
					}
				}
			}

			blurredImage[index] = Color(totalR / numSamples, totalG / numSamples, totalB / numSamples);
		}
	}

	return blurredImage;
}
