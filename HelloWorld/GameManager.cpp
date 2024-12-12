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
}

