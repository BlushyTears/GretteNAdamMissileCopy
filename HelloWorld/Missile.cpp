#include "Missile.h"
#include "Play.h"

void initExplosionList(Explosion& expl, size_t& initialCapacity) {
	expl.explosionPositions = new Play::Point2f[initialCapacity];
	expl.radiuses = new int[initialCapacity];
	expl.explosionCount = 0;
	expl.explosionCapacity = initialCapacity;
}

void addExplosion(Explosion& expl, Play::Point2f explPos) {
	if (expl.explosionCount >= expl.explosionCapacity) {
		size_t newCapacity = expl.explosionCapacity * 2;

		Play::Point2f* newExplosionPositions = new Play::Point2f[newCapacity];
		int* newRadiuses = new int[newCapacity];

		for (size_t i = 0; i < expl.explosionCount; i++) {
			newExplosionPositions[i] = expl.explosionPositions[i];
			newRadiuses[i] = expl.radiuses[i];
		}

		delete[] expl.explosionPositions;
		delete[] expl.radiuses;

		expl.explosionPositions = newExplosionPositions;
		expl.radiuses = newRadiuses;
	}

	expl.explosionPositions[expl.explosionCount] = explPos;
	expl.radiuses[expl.explosionCount] = 0;
	expl.explosionCount++;
}

void removeExplosion(Explosion& expl, size_t explIndex) {
	if (explIndex < expl.explosionCount) {
		for (size_t i = explIndex; i < expl.explosionCount - 1; i++) {
			expl.explosionPositions[i] = expl.explosionPositions[i + 1];
			expl.radiuses[i] = expl.radiuses[i + 1];
		}
		expl.explosionCount--;
	}
}

void initMissileList(Missile& missileList, size_t& initialCapacity) {
	missileList.startingPositions = new Play::Point2f[initialCapacity];
	missileList.currentPositions = new Play::Point2f[initialCapacity];
	missileList.endingPositions = new Play::Point2f[initialCapacity];

	missileList.colours = new MyColor[initialCapacity];
	missileList.distancesTravelled = new float[initialCapacity];
	missileList.missilesToBeDestroyed = new bool[initialCapacity];

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
		bool* newMissilesToBeDestroyed = new bool[newCapacity];

		for (size_t i = 0; i < missileList.missileCount; i++) {
			newStartingPos[i] = missileList.startingPositions[i];
			newCurrentPos[i] = missileList.currentPositions[i];
			newEndingPos[i] = missileList.endingPositions[i];
			newColor[i] = missileList.colours[i];
			newDistancesTraveled[i] = missileList.distancesTravelled[i];
			newMissilesToBeDestroyed[i] = missileList.missilesToBeDestroyed[i];
		}

		delete[] missileList.startingPositions;
		delete[] missileList.currentPositions;
		delete[] missileList.endingPositions;
		delete[] missileList.colours;
		delete[] missileList.distancesTravelled;
		delete[] missileList.missilesToBeDestroyed;

		missileList.startingPositions = newStartingPos;
		missileList.currentPositions = newCurrentPos;
		missileList.endingPositions = newEndingPos;
		missileList.colours = newColor;
		missileList.distancesTravelled = newDistancesTraveled;
		missileList.missilesToBeDestroyed = newMissilesToBeDestroyed;

		missileList.missileCapacity = newCapacity;
	}

	missileList.startingPositions[missileList.missileCount] = _startingPos;
	missileList.currentPositions[missileList.missileCount] = _startingPos; // current pos is initially same as starting pos (naturally)
	missileList.endingPositions[missileList.missileCount] = _endingPos;
	missileList.colours[missileList.missileCount] = _myColor;
	missileList.distancesTravelled[missileList.missileCount] = 0.0f;
	missileList.missilesToBeDestroyed[missileList.missileCount] = false;

	missileList.missileCount++;
}

// shift all missiles after the one about get deleted by one step backwards
// Example: [1,2,3] we wanna delete 2 ->
// missileList[1] = missileList[1 + 1] and then reduce the list by one.
// addMissile() is what replaces the forgotten about element below which is meme-able to say the least
void deleteMissile(Missile& missileList, size_t missileIndex) {
	if (missileIndex < missileList.missileCount) {
		for (size_t i = missileIndex; i < missileList.missileCount - 1; i++) {
			missileList.startingPositions[i] = missileList.startingPositions[i + 1];
			missileList.currentPositions[i] = missileList.currentPositions[i + 1];
			missileList.endingPositions[i] = missileList.endingPositions[i + 1];
			missileList.colours[i] = missileList.colours[i + 1];
			missileList.distancesTravelled[i] = missileList.distancesTravelled[i + 1];
			missileList.missilesToBeDestroyed[i] = missileList.missilesToBeDestroyed[i + 1];
		}
		missileList.missileCount--;
	}
}

// 0, 1, 2, 3
// addMissile(4) ->
// 0, 1, 2, 3, 4
// deleteMissile(2) ->
// 0, 1,  

// This is probably a good implementation, but we aren't doing radius checking yet, so it's wrong biz logic
//void checkChain(Missile& missileList, int i) {
//	if (missileList.distancesTravelled[i] >= (missileList.startingPositions[i] - missileList.endingPositions[i]).Length()) {
//		missileList.missilesToBeDestroyed[i] = true;
//		checkChain(missileList, i + 1);
//	}
//}

void updateMissilesPositions(Missile& missileList, Explosion& expl, float deltatime) {
	if (missileList.missileCount > 0) {
		for (int i = 0; i < missileList.missileCount; i++) {
			missileList.distancesTravelled[i] += 20 * deltatime;

			Play::Vector2D direction = (missileList.endingPositions[i] - missileList.startingPositions[i]);
			direction.Normalize();
			Play::Vector2D velocity = direction * 1; // the 1 is hardcoded for speed, maybe refactor l8er
			missileList.currentPositions[i] += velocity * deltatime;
			missileList.currentPositions[i] = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];

			// We probably wanna draw the endpoint of the missile here too
			Play::Point2D endPoint = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];
			Play::DrawLine(missileList.startingPositions[i], endPoint, Play::cRed);

			if (missileList.distancesTravelled[i] >= (missileList.startingPositions[i] - missileList.endingPositions[i]).Length()) {
				addExplosion(expl, missileList.currentPositions[i]);
				deleteMissile(missileList, i);
				Play::PlayAudio("Explode");
			}
		}
	}
}

// void delete missile function here when it explodes
void cleanUpMissiles(Missile& missileList, Explosion& expl) {
	delete[] missileList.startingPositions;
	delete[] missileList.currentPositions;
	delete[] missileList.endingPositions;
	delete[] missileList.colours;
	delete[] missileList.distancesTravelled;

	// i'm too lazy to put these within its own function (if that's even a good idea)
	delete[] expl.explosionPositions;
	delete[] expl.radiuses;
}




