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


}