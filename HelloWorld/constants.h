#pragma once
const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 360;
const int DISPLAY_SCALE = 2;

enum Heading {
	NORTH,
	SOUTH,
	WEST,
	EAST
};

namespace MyPoint {
	struct Point2D {
		int x;
		int y;
	};
}

struct Color {
	float r;
	float g;
	float b;
};

