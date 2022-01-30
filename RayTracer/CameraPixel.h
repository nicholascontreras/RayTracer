#pragma once

#include <vector>
#include "Color.h"

class CameraPixel {
private:
	std::vector<Color> colorsReceived = {};

public:
	~CameraPixel() {
		colorsReceived.clear();
	}

	void addIncomingRay(Color color);
	unsigned int getNumRaysReceived();
	Color getAverageColor();
};

