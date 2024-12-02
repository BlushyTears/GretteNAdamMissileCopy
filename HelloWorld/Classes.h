#pragma once
#include "Play.h"
#include "constants.h"

class Apple {
	public:
		int radius;
		MyPoint::Point2D pos;
		Apple();
		void draw();  
};

class SnakePart {
	public:
		MyPoint::Point2D pos;
		Color c;
		SnakePart(int x, int y);
		SnakePart();
		void draw();
};

class SnakeHead {
	public:
		Heading h;
		MyPoint::Point2D pos;
		Color c;
		int snakeparts;
		int radius;
		SnakePart* s;

		SnakeHead();
		~SnakeHead();
		void draw();
		void move();
		void handleInput();
		void addPart(int partsToAdd);
		void drawChildren();
		bool isColliding(Apple* applePtr);
};

