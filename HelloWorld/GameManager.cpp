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
	GameManager::missileBasesList = new MissileBase*[NUM_BASES];
	missileList = new Missile;
	size_t initialCapacity = 16;

	initMissileList(*missileList, initialCapacity);

	for (int i = 0; i < NUM_BASES; i++) {
		missileBasesList[i] = nullptr;
	}
}

GameManager::~GameManager() {
	for (int i = 0; i < NUM_BASES; i++) {
		deallocateData(*missileBasesList[i]);
		delete missileBasesList[i];
	}
	delete[] missileBasesList;
	cleanUpMissiles(*missileList);
	delete[] missileList;
}

// This function initiate stuff and add spacing between the Buildings
void GameManager::setupGame() {
	float usableWidth = DISPLAY_WIDTH * 2 / 3;
	float startX = DISPLAY_WIDTH / 6;
	float spacing = usableWidth / (NUM_BASES - 1);

	for (int i = 0; i < NUM_BASES; i++) {
		float xPos = startX + spacing * i; 
		missileBasesList[i] = initMissileBase({ xPos, DISPLAY_HEIGHT / 7 });
	}
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

	updateMissilesPositions(*missileList, elapsedTime);
	drawData();
	Play::Point2D mp = Play::Input::GetMousePos();
	Play::DrawLine({ mp.x - rhs, mp.y }, { mp.x + rhs, mp.y }, Play::cGreen);
	Play::DrawLine({ mp.x, mp.y + rhs }, {mp.x, mp.y - rhs }, Play::cGreen);
}

// draws active objects (or data since no OOP) on the screen
void GameManager::drawData() {
	Play::DrawRect(Play::Point2D(0, 0), Play::Point2D(DISPLAY_WIDTH, DISPLAY_HEIGHT / 7), Play::cYellow, true);

	for (int i = 0; i < 3; i++) {
		Play::DrawSprite(spriteTable[missileBasesList[i]->spriteID],
			{ missileBasesList[i]->missileBase->pos->x, missileBasesList[i]->missileBase->pos->y
		}, 0);

		Play::DrawSprite(spriteTable[missileBasesList[i]->adjCities->spriteID],
			{ missileBasesList[i]->missileBase->pos->x + 20,
					missileBasesList[i]->missileBase->pos->y
		}, 0);

		Play::DrawSprite(spriteTable[missileBasesList[i]->adjCities->spriteID],
			{ missileBasesList[i]->missileBase->pos->x - 20,
					missileBasesList[i]->missileBase->pos->y
		}, 0);
	}

	// Draw all the hitmarkers for missiles here
	for (int i = 0; i < missileList->missileCount; i++) {
		Play::DrawCircle({ missileList->endingPositions[i].x, missileList->endingPositions[i].y }, 2,
			{ missileList->colours[i].r, missileList->colours[i].g, missileList->colours[i].g });

		// We probably wanna draw the missiles and their endpoints here
	} 
}

// References to drawing missile stuff
//void Missile::Draw()
//{
//	Play::Vector2D direction = this->GetTravellingDirection();
//
//	Play::Point2D endPoint = this->origin + direction * distanceTravelled;
//
//	Play::DrawLine(this->origin, endPoint, this->colour);
//
//	const Play::Colour colours[4] = {
//		Play::cWhite,
//		Play::cRed,
//		Play::cBlue,
//		Play::cYellow
//	};
//
//	this->alternateColour = (this->alternateColour + 1) % 8;
//	int colourIndex = this->alternateColour / 2;
//
//	Play::DrawPixel(endPoint, colours[colourIndex]);
//
//	// Draw Target
//	Play::DrawCircle(this->target, 2, this->colour);
//}
//
//void Missile::Simulate(float elapsedTime)
//{
//	this->distanceTravelled += this->speed * elapsedTime;
//	Play::Vector2D direction = this->GetTravellingDirection();
//	Play::Point2D currentPosition = this->origin + direction * distanceTravelled;
//	this->SetPosition(currentPosition);
//
//	if (distanceTravelled >= GetDistanceFromOriginToTarget() || this->IsDestroyed())
//	{
//		Explosion* explosion = new Explosion(this->GetPosition());
//		this->gameStateManager->AddGameObject(explosion);
//
//		// Destroy this object
//		this->ScheduleDelete();
//	}
//}