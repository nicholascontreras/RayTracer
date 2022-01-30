#include "CameraPixel.h"

void CameraPixel::addIncomingRay(Color color) {
	colorsReceived.push_back(color);
}

unsigned int CameraPixel::getNumRaysReceived() {
	return colorsReceived.size();
}

Color CameraPixel::getAverageColor() {
	if (colorsReceived.empty()) {
		return Color(0, 0, 0);
	}
	else {
		double totalRed = 0, totalGreen = 0, totalBlue = 0;

		for (int i = 0; i < colorsReceived.size(); i++) {
			totalRed += colorsReceived[i].getRed();
			totalGreen += colorsReceived[i].getGreen();
			totalBlue += colorsReceived[i].getBlue();
		}

		return Color(totalRed / colorsReceived.size(), totalGreen / colorsReceived.size(), totalBlue / colorsReceived.size());
	}
}
