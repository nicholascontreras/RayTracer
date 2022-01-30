#pragma once
#include <stdexcept>
class Color {
private:
	double red, green, blue;

public:
	Color(double red, double green, double blue) : red(red), green(green), blue(blue) {
		if (red < 0 || red > 1) {
			throw std::invalid_argument("Red value must be between 0 and 1!");
		} else if (green < 0 || green > 1) {
			throw std::invalid_argument("Green value must be between 0 and 1!");
		} else if (blue < 0 || blue > 1) {
			throw std::invalid_argument("Blue value must be between 0 and 1!");
		}
	}

	Color() : Color(0, 0, 0) {}

	double getRed();
	double getGreen();
	double getBlue();

	unsigned short getRedAsInt();
	unsigned short getGreenAsInt();
	unsigned short getBlueAsInt();

	Color scaleBy(Color other);
	Color scale(double scaler);
};

