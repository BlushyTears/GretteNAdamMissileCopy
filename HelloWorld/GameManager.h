#pragma once
#include "Buildings.h"
#include "Missile.h"

class GameManager
{
	public:
		GameManager();
		~GameManager();

		void frame(float elapsedTime);
		void drawData();
		MissileBase* missileBasesList; // list of all missile bases
		Missile* missileList; // list of all active missiles
		Explosion* explosionList; // (separated from missiles, as when the missile is deleted, we still need pos to display explosion)

	private:
		float reloadTime = 0.2;
		float timeSinceFire = 0;
};

