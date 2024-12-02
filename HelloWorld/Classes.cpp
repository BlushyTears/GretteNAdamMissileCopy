#include "Classes.h"
#include "constants.h"
#include "Play.h"

#include <stdexcept>

Apple::Apple() {
	radius = 10;

	pos.x = Play::RandomRollRange(radius, DISPLAY_WIDTH - radius);
	pos.y = Play::RandomRollRange(radius, DISPLAY_HEIGHT - radius);
}


void Apple::draw() {
	Play::DrawCircle({ pos.x, pos.y}, radius, Play::cRed);
}

// SnakePart
SnakePart::SnakePart(int x, int y) {
	pos.x = x;
	pos.y = y;

	c.r = Play::RandomRollRange(20, 255);
	c.g = Play::RandomRollRange(20, 255);
	c.b = Play::RandomRollRange(20, 255);
}

SnakePart::SnakePart() {
	pos.x = 0;
	pos.y = 0;
}

void SnakePart::draw() {
	Play::DrawCircle({ pos.x, pos.y }, 10, { c.r, c.g, c.b });
}

// SnakeHead
SnakeHead::SnakeHead() {
	pos.x = 50;
	pos.y = 50;
	radius = 10;
	addPart(2);
}

SnakeHead::~SnakeHead() {
	delete[] s;
}

void SnakeHead::draw() {
	Play::DrawCircle({ pos.x, pos.y }, radius, Play::cBlue);
}

void SnakeHead::drawChildren() {
	for (int i = 0; i < snakeparts; i++) {
		s[i].draw();
	}
}

void SnakeHead::handleInput() {
	if (Play::KeyPressed(Play::KEY_UP)) {
		h = Heading::NORTH;
	}
	if (Play::KeyPressed(Play::KEY_DOWN)) {
		h = Heading::SOUTH;
	}
	if (Play::KeyPressed(Play::KEY_LEFT)) {
		h = Heading::WEST;
	}
	if (Play::KeyPressed(Play::KEY_RIGHT)) {
		h = Heading::EAST;
	}
}

void SnakeHead::move() {
	if (h == Heading::NORTH) {
		pos.y += 15;
	}
	if (h == Heading::SOUTH) {
		pos.y -= 15;
	}
	if (h == Heading::WEST) {
		pos.x -= 15;
	}
	if (h == Heading::EAST) {
		pos.x += 15;
	}

	for (int i = snakeparts - 1; i > 0; i--) {
		s[i].pos.x = s[i - 1].pos.x;
		s[i].pos.y = s[i - 1].pos.y;
	}

	s[0].pos.x = pos.x;
	s[0].pos.y = pos.y;

	draw();

	for (int i = 0; i < snakeparts; i++) {
		s[i].draw();
	}
}

bool SnakeHead::isColliding(Apple* applePtr) {
	int xDiff = int(pos.x) - (applePtr->pos.x);
	int yDiff = int(pos.y) - (applePtr->pos.y);

	int rad = applePtr->radius + radius;

	return((xDiff * xDiff) + (yDiff * yDiff) < (rad * rad));
}

void SnakeHead::addPart(int partsToAdd) {
	if (partsToAdd < 0) {
		throw std::invalid_argument("Size to increase by has to be positive");
	}

	int newSize = partsToAdd + snakeparts;

	SnakePart* newParts = new SnakePart[newSize];  
	for (int i = 0; i < snakeparts; i++) {
		newParts[i] = s[i];  
	}

	// necessary bolognuese cause head and tail are not the same
	for (int i = snakeparts; i < newSize; i++) {  
		if (snakeparts < 2) {
			if (h == Heading::NORTH) {
				newParts[i] = SnakePart(pos.x, pos.y - 15);
			}
			if (h == Heading::SOUTH) {
				newParts[i] = SnakePart(pos.x, pos.y + 15);
			}
			if (h == Heading::WEST) {
				newParts[i] = SnakePart(pos.x - 15, pos.y);
			}
			if (h == Heading::EAST) {
				newParts[i] = SnakePart(pos.x + 15, pos.y);
			}
		}
		else if (snakeparts >= 2){
			if (h == Heading::NORTH) {
			newParts[i] = SnakePart(s->pos.x, s->pos.y - 15);
			}
			if (h == Heading::SOUTH) {
				newParts[i] = SnakePart(s->pos.x, s->pos.y + 15);
			}
			if (h == Heading::WEST) {
				newParts[i] = SnakePart(s->pos.x - 15, s->pos.y);
			}
			if (h == Heading::EAST) {
				newParts[i] = SnakePart(s->pos.x + 15, s->pos.y);
			}
		}
	}

	delete[] s;

	s = newParts;
	snakeparts = newSize;
}

 // Play.h reference for collision:
//bool IsColliding(GameObject& object1, GameObject& object2)
//{
//	//Don't collide with noObject
//	if (object1.type == -1 || object2.type == -1)
//		return false;
//
//	int xDiff = int(object1.pos.x) - int(object2.pos.x);
//	int yDiff = int(object1.pos.y) - int(object2.pos.y);
//	int radii = object2.radius + object1.radius;
//
//	// Game progammers don't do square root!
//	return((xDiff * xDiff) + (yDiff * yDiff) < radii * radii);
//}



