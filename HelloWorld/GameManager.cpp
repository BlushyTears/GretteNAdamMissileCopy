#include "GameManager.h"
#include "Buildings.h"
#include "constants.h"
#include "Missile.h"
#include "Play.h"

// We define spriteTable semi-locally, because the compiler cries like a baby otherwise for some reason
const char* spriteTable[] = { "city", "missile_base", "rubble" };
const int rhs = 2; // rhs = reticleHalfSize

Rendering render;

// Constructor
GameManager::GameManager() {
	// Allocate memory for missileBasesList
	missileBasesList = new MissileBase;
	missileList = new Missile;
	explosionList = new Explosion;
	size_t initialCapacity = 16;

	initMissileBases(*missileBasesList, initialCapacity); // missile bases probably better off having a capacity of 4
	initMissileList(*missileList, initialCapacity);
	initExplosionList(*explosionList, initialCapacity);
}

GameManager::~GameManager() {
	deallocateData(*missileBasesList);
	cleanUpMissiles(*missileList, *explosionList);
	delete[] missileBasesList;
	delete[] missileList;
	delete[] explosionList;
}

// Called 60 times a second
int timePassed = 0;
void GameManager::frame(float elapsedTime) {
	timeSinceFire += elapsedTime;
	if (Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT)) {
		if (timeSinceFire >= reloadTime) {
			// GetClosestMissileBase here
			addMisile(*missileList, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 4 }, Play::Input::GetMousePos(), MyColor(0, 0, 255, 1));
			Play::PlayAudio("Fire");
			timeSinceFire = 0;
		}
	}

	if (timePassed % 120 == 0) {
		addMisile(*missileList, { Play::RandomRollRange(5, DISPLAY_WIDTH - 5) , DISPLAY_HEIGHT }, 
		{ Play::RandomRollRange(5, DISPLAY_WIDTH - 5) , DISPLAY_HEIGHT / 7 }, MyColor(255, 0, 0, 1));
		Play::PlayAudio("Fire");
	}
	timePassed++;

	updateMissilesPositions(*missileList, *explosionList, elapsedTime);
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(DISPLAY_WIDTH, DISPLAY_HEIGHT / 7), Play::cYellow, true);
	render.renderStuff(*missileBasesList, *missileList, *explosionList);

	// Draw all the reticle for each missile here
	for (int i = 0; i < missileList->missileCount; i++) {
		Play::DrawCircle({ missileList->endingPositions[i].x, missileList->endingPositions[i].y }, 2,
			{ Play::cBlue });

		Play::Vector2D direction = (missileList->endingPositions[i] - missileList->startingPositions[i]);
		direction.Normalize();
		missileList->currentPositions[i] = missileList->startingPositions[i] + direction * missileList->distancesTravelled[i];

		Play::Point2D endPoint = missileList->startingPositions[i] + direction * missileList->distancesTravelled[i];
		Play::DrawLine(missileList->startingPositions[i], endPoint,
			{ missileList->colours[i].r, missileList->colours[i].g, missileList->colours[i].b });
		Play::DrawPixel(endPoint, Play::cGreen); // maybe vary this with red and blue or something
	}
	// We probably wanna draw the missiles and their endpoints before the explosions
	for (int i = 0; i < explosionList->explosionCount; i++) {
		Play::DrawCircle({ explosionList->explosionPositions[i].x, explosionList->explosionPositions[i].y },
			explosionList->radiuses[i], Play::cRed);

		for (int j = 0; j < missileList->missileCount; j++) {
			if (abs(missileList->currentPositions[j].Length() - explosionList->explosionPositions[i].Length()) <= explosionList->radiuses[i]) {
				addExplosion(*explosionList, missileList->currentPositions[j]);
				deleteMissile(*missileList, j);
			}
		}
		if (explosionList->radiuses[i] >= 10) {
			removeExplosion(*explosionList, i);
		}
		explosionList->radiuses[i]++;
	}
}

