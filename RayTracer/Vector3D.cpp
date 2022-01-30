#include "Vector3D.h"
#include <stdlib.h>
#include <math.h>
#include <stdexcept>
#include <string>
#include <iostream>

double randomUnitDouble() {
	return (((double)rand() / RAND_MAX) * 2) - 1;
}

Vector3D Vector3D::randomUnitVector() {
	Vector3D vector;

	while (true) {
		vector = Vector3D(randomUnitDouble(), randomUnitDouble(), randomUnitDouble());

		if (vector.getMagnitude() <= 1) {
			return vector.normalize();
		}
	}
}

double Vector3D::getX() {
	return this->x;
}

double Vector3D::getY() {
	return this->y;
}

double Vector3D::getZ() {
	return this->z;
}

double Vector3D::getMagnitude() {
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

Vector3D Vector3D::normalize() {
	double mag = getMagnitude();
	return Vector3D(x / mag, y / mag, z / mag);
}

bool Vector3D::isNormal() {
	// Say a vector is normal if it's very close
	return abs(getMagnitude() - 1) < 0.00001;
}

Vector3D Vector3D::scale(double scaler) {
	return Vector3D(x * scaler, y * scaler, z * scaler);
}

double Vector3D::dotProduct(Vector3D other) {
	return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::crossProduct(Vector3D other) {
	double crossX = y * other.z - z * other.y;
	double crossY = -(x * other.z - z * other.x);
	double crossZ = x * other.y - y * other.x;
	return Vector3D(crossX, crossY, crossZ);
}

Vector3D Vector3D::directionTo(Vector3D other) {
	return (other - *this).normalize();
}

double Vector3D::angleBetween(Vector3D other) {
	return acos(this->dotProduct(other) / (getMagnitude() * other.getMagnitude()));
}

std::string Vector3D::toString() {
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

double radToDegrees(double rad) {
	return rad * (180.0 / 3.141592653589793238463);
}

void Vector3D::tests() {
	std::cout << "--- Begin Vector Tests ---" << std::endl;

	std::cout << (Vector3D(1, 2, 3).dotProduct(Vector3D(4, -5, 6)) == 12) << std::endl;
	std::cout << (Vector3D(-4, -9, 0).dotProduct(Vector3D(-1, 2, 0)) == -14) << std::endl;
	std::cout << (Vector3D(-1, 2, 0).dotProduct(Vector3D(-4, -9, 0)) == -14) << std::endl;
	std::cout << (Vector3D(6, -1, 3).dotProduct(Vector3D(4, 18, -2)) == 0) << std::endl;

	std::cout << (Vector3D(3, -3, 1).crossProduct(Vector3D(4, 9, 2)) == Vector3D(-15, -2, 39)) << std::endl;
	std::cout << (Vector3D(3, -3, 1).crossProduct(Vector3D(-12, 12, -4)) == Vector3D(0, 0, 0)) << std::endl;
	std::cout << (Vector3D(2, 3, 4).crossProduct(Vector3D(5, 6, 7)) == Vector3D(-3, 6, -3)) << std::endl;

	std::cout << (radToDegrees(Vector3D(5, 0, 0).angleBetween(Vector3D(5, 0, 0))) == 0) << std::endl;
	std::cout << (radToDegrees(Vector3D(5, 0, 0).angleBetween(Vector3D(-5, 0, 0))) == 180) << std::endl;
	std::cout << (radToDegrees(Vector3D(5, 0, 0).angleBetween(Vector3D(0, 3, 0))) == 90) << std::endl;
	std::cout << (radToDegrees(Vector3D(5, 0, 0).angleBetween(Vector3D(0, -5, 0))) == 90) << std::endl;
	std::cout << (abs(radToDegrees(Vector3D(5, 0, 0).angleBetween(Vector3D(5, -5, 0))) - 45) < .0001) << std::endl;

	std::cout << "--- End Vector Tests ---" << std::endl;
}
