#pragma once

#include <string>
class Vector3D {
private:
	double x, y, z;

public:

	Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3D() : Vector3D(0, 0, 0) {};

	static Vector3D randomUnitVector();

	double getX();
	double getY();
	double getZ();

	double getMagnitude();
	Vector3D normalize();
	bool isNormal();
	Vector3D scale(double scaler);
	double dotProduct(Vector3D other);
	Vector3D crossProduct(Vector3D other);
	Vector3D directionTo(Vector3D other);
	double angleBetween(Vector3D other);

	Vector3D operator+ (Vector3D other) {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D operator- (Vector3D other) {
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}

	bool operator== (Vector3D other) {
		return x == other.x && y == other.y && z == other.z;
	}

	std::string toString();

	static void tests();
};

