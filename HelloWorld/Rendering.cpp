#include "Rendering.h"
#include "Buildings.h"
#include "Missile.h"
#include "constants.h"

// lol about this spriteTable multiple definition
const char* spriteTable2[] = { "city", "missile_base", "rubble" };
const int rhs = 2; // rhs = reticleHalfSize

void Rendering::renderStuff(MissileBase& missileBasesList, Missile& missileList, Explosion& explosionList) {

	// Draw crosshair to follow mouse
	Play::Point2D mp = Play::Input::GetMousePos();
	Play::DrawLine({ mp.x - rhs, mp.y }, { mp.x + rhs, mp.y }, Play::cGreen);
	Play::DrawLine({ mp.x, mp.y + rhs }, { mp.x, mp.y - rhs }, Play::cGreen);

	for (int i = 0; i < 3; i++) {
		Play::DrawSprite(spriteTable2[*(missileBasesList.missileBase[i]->spriteID)],
			{
				missileBasesList.missileBase[i]->pos->x,
				missileBasesList.missileBase[i]->pos->y
			}
		, 0);

		// we cast int to const char cause play.h bad
		std::string tempString = std::to_string(missileBasesList.currentAmmo[i]);
		const char* charText = tempString.c_str();

		Play::DrawDebugText(
			{
				missileBasesList.missileBase[i]->pos->x,
				missileBasesList.missileBase[i]->pos->y - 10
			},
			charText, Play::cBlack);
	}

	// draw adj cities
	for (int i = 0; i < 6; i++) {
		Play::DrawSprite(spriteTable2[*(missileBasesList.adjCities[i]->spriteID)],
			{
				missileBasesList.adjCities[i]->pos->x,
				missileBasesList.adjCities[i]->pos->y
			}
		, 0);
	}

	// Draw all the reticle for each missile here
	for (int i = 0; i < missileList.missileCount; i++) {
		Play::DrawCircle({ missileList.endingPositions[i].x, missileList.endingPositions[i].y }, 2,
			{ Play::cBlue });

		Play::Vector2D direction = (missileList.endingPositions[i] - missileList.startingPositions[i]);
		direction.Normalize();
		missileList.currentPositions[i] = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];

		Play::Point2D endPoint = missileList.startingPositions[i] + direction * missileList.distancesTravelled[i];
		Play::DrawLine(missileList.startingPositions[i], endPoint,
			{missileList.colours[i].r, missileList.colours[i].g, missileList.colours[i].b });
		Play::DrawPixel(endPoint, Play::cGreen); // maybe vary this with red and blue or something
	}
	// We probably wanna draw the missiles and their endpoints before the explosions
	for (int i = 0; i < explosionList.explosionCount; i++) {
		Play::DrawCircle({ explosionList.explosionPositions[i].x, explosionList.explosionPositions[i].y },
			explosionList.radiuses[i], Play::cRed);

		for (int j = 0; j < missileList.missileCount; j++) {
			if (abs(missileList.currentPositions[j].Length() - explosionList.explosionPositions[i].Length()) <= explosionList.radiuses[i]) {
				addExplosion(explosionList, missileList.currentPositions[j]);
				deleteMissile(missileList, j);
			}
		}
		if (explosionList.radiuses[i] >= 10) {
			removeExplosion(explosionList, i);
		}
		explosionList.radiuses[i]++;
	}
}