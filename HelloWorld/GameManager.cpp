#include "GameManager.h"
#include "Buildings.h"
#include "constants.h"
#include "Missile.h"
#include "Play.h"

// We define spriteTable locally, because the compiler cries like a baby otherwise for some reason
const char* spriteTable[] = { "city", "missile_base", "rubble" };
const int rhs = 2; // rhs = reticleHalfSize

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
	delete missileBasesList;
	delete missileList;
	delete explosionList;
}

// Called 60 times a second
void GameManager::frame(float elapsedTime) {
	timeSinceFire += elapsedTime;
	if (Play::Input::GetMouseDown(Play::Input::MouseButton::BUTTON_LEFT)) {
		if (timeSinceFire >= reloadTime) {
			addMisile(*missileList, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 4 }, Play::Input::GetMousePos(), MyColor(255, 0, 0, 1));
			Play::PlayAudio("Fire");
			timeSinceFire = 0;
		}
	}

	updateMissilesPositions(*missileList, *explosionList, elapsedTime);
	drawData();
	Play::Point2D mp = Play::Input::GetMousePos();
	Play::DrawLine({ mp.x - rhs, mp.y }, { mp.x + rhs, mp.y }, Play::cGreen);
	Play::DrawLine({ mp.x, mp.y + rhs }, {mp.x, mp.y - rhs }, Play::cGreen);
}

// draws active objects (or data since no OOP) on the screen
void GameManager::drawData() {
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(DISPLAY_WIDTH, DISPLAY_HEIGHT / 7), Play::cYellow, true);

	// draw bases and their adjacent cities
	for (int i = 0; i < 3; i++) {
		Play::DrawSprite(spriteTable[*(missileBasesList->missileBase[i]->spriteID)],
			{ 
				missileBasesList->missileBase[i]->pos->x,
				missileBasesList->missileBase[i]->pos->y
			}
		, 0);
	}

	for (int i = 0; i < 6; i++) {
		Play::DrawSprite(spriteTable[*(missileBasesList->adjCities[i]->spriteID)],
			{ 
				missileBasesList->adjCities[i]->pos->x,
				missileBasesList->adjCities[i]->pos->y
			}
		, 0);
	}

	// Draw all the hitmarkers for missiles here
	for (int i = 0; i < missileList->missileCount; i++) {
		Play::DrawCircle({ missileList->endingPositions[i].x, missileList->endingPositions[i].y }, 2,
						 { missileList->colours[i].r, missileList->colours[i].g, missileList->colours[i].g });

		// We probably wanna draw the missiles and their endpoints here
	} 
	for (int i = 0; i < explosionList->explosionCount; i++) {
		Play::DrawCircle({ explosionList->explosionPositions[i].x, explosionList->explosionPositions[i].y }, 
						   explosionList->radiuses[i], Play::cRed );

		for (int j = 0; j < missileList->missileCount; j++) {
			if (i == j)
				continue;
			if (abs(missileList->currentPositions[j].Length() - explosionList->explosionPositions[i].Length()) <= explosionList->radiuses[i]) {
				addExplosion(*explosionList, missileList->currentPositions[j]);
				deleteMissile(*missileList, j);
			}
		}

		if (explosionList->radiuses[i] >= 12) {
			removeExplosion(*explosionList, i);
		}
		explosionList->radiuses[i]++;
	}
}
