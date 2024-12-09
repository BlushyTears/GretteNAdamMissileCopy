#pragma once
#include "Buildings.h"
#include "Missile.h"

class GameManager
{
	public:
		GameManager();
		~GameManager();

		void setupGame();
		void frame(float elapsedTime);
		void drawData();
		MissileBase** missileBasesList; // list of all missile bases
		Missile* missileList; // list of all active missiles
	private:
		float reloadTime = 0.2;
		float timeSinceFire = 0;
};

