#include "Color.h"

double Color::getRed() {
	return red;
}

double Color::getGreen() {
	return green;
}

double Color::getBlue() {
	return blue;
}

unsigned short Color::getRedAsInt() {
	return (unsigned short) round(red * 255);
}

unsigned short Color::getGreenAsInt() {
	return (unsigned short) round(green * 255);
}

unsigned short Color::getBlueAsInt() {
	return (unsigned short) round(blue * 255);
}

Color Color::scaleBy(Color other) {
	return Color(red * other.red, green * other.green, blue * other.blue);
}

Color Color::scale(double scaler) {
	return Color(red * scaler, green * scaler, blue * scaler);
}