#include "Missile.h"
#include "Play.h"

void initMissileList(Missile& missileList, size_t& initialCapacity) {
	missileList.startingPositions = new Play::Point2f[initialCapacity];
	missileList.currentPositions = new Play::Point2f[initialCapacity];
	missileList.endingPositions = new Play::Point2f[initialCapacity];

	missileList.colours = new MyColor[initialCapacity];
	missileList.distancesTravelled = new float[initialCapacity];

	missileList.missileCount = 0;
	missileList.missileCapacity = initialCapacity;
}

void addMisile(Missile& missileList, Play::Point2f _startingPos, Play::Point2f _endingPos, MyColor _myColor) {
	if (missileList.missileCount >= missileList.missileCapacity) {
		size_t newCapacity = missileList.missileCapacity * 2;

		Play::Point2f* newStartingPos = new Play::Point2f[newCapacity];
		Play::Point2f* newCurrentPos = new Play::Point2f[newCapacity];
		Play::Point2f* newEndingPos = new Play::Point2f[newCapacity];
		MyColor* newColor = new MyColor[newCapacity];

		float* newDistancesTraveled = new float[newCapacity]; 

		for (size_t i = 0; i < missileList.missileCount; i++) {
			newStartingPos[i] = missileList.startingPositions[i];
			newCurrentPos[i] = missileList.currentPositions[i];
			newEndingPos[i] = missileList.endingPositions[i];
			newColor[i] = missileList.colours[i];
			newDistancesTraveled[i] = missileList.distancesTravelled[i];
		}

		delete[] missileList.startingPositions;
		delete[] missileList.currentPositions;
		delete[] missileList.endingPositions;
		delete[] missileList.colours;
		delete[] missileList.distancesTravelled;

		missileList.startingPositions = newStartingPos;
		missileList.currentPositions = newCurrentPos;
		missileList.endingPositions = newEndingPos;
		missileList.colours = newColor;
		missileList.distancesTravelled = newDistancesTraveled;

		missileList.missileCapacity = newCapacity;
	}

	missileList.startingPositions[missileList.missileCount] = _startingPos;
	missileList.currentPositions[missileList.missileCount] = _startingPos; // current pos is initially same as starting pos (naturally)
	missileList.endingPositions[missileList.missileCount] = _endingPos;
	missileList.colours[missileList.missileCount] = _myColor;
	missileList.distancesTravelled[missileList.missileCount] = 0.0f;

	missileList.missileCount++;
}

// shift all missiles after the one about get deleted by one step backwards
// Example: [1,2,3] we wanna delete 2 ->
// missileList[1] = missileList[1 + 1] and then reduce the list by one.
// addMissile() is what replaces the forgotten about element below which is meme-able to say the least
void deleteMissile(Missile& missileList, size_t missileIndex) {
	if (missileIndex < missileList.missileCount) {
		for (size_t i = 0; i < missileList.missileCount - 1; i++) {
			missileList.startingPositions[i] = missileList.startingPositions[i + 1];
			missileList.currentPositions[i] = missileList.currentPositions[i + 1];
			missileList.endingPositions[i] = missileList.endingPositions[i + 1];
			missileList.colours[i] = missileList.colours[i + 1];
			missileList.distancesTravelled[i] = missileList.distancesTravelled[i + 1];

		}
		missileList.missileCount--;
	}
}

void updateMissilesPositions(Missile& missileList, float deltatime) {
	if (missileList.missileCount > 0) {
		for (int i = 0; i < missileList.missileCount; i++) {
			missileList.distancesTravelled[i] += 20 * deltatime;

			Play::Vector2D direction = (missileList.endingPositions[i] - missileList.startingPositions[i]);
			direction.Normalize();
			Play::Vector2D velocity = direction * 1; // the 1 is hardcoded for speed, maybe refactor l8er
			missileList.currentPositions[i] += velocity * deltatime;
			missileList.currentPositions[i] = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];

			if (missileList.distancesTravelled[i] >= (missileList.startingPositions[i] - missileList.endingPositions[i]).Length()) {
				deleteMissile(missileList, i);
				Play::PlayAudio("Explode");
				continue;
			}

			// We probably wanna draw the endpoint of the missile here
			 Play::Point2D endPoint = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];
			 Play::DrawLine(missileList.startingPositions[i], endPoint, Play::cRed);
		}
	}
}

// void delete missile function here when it explodes
void cleanUpMissiles(Missile& missileList) {
	delete[] missileList.startingPositions;
	delete[] missileList.currentPositions;
	delete[] missileList.endingPositions;
	delete[] missileList.colours;
	delete[] missileList.distancesTravelled;
}




