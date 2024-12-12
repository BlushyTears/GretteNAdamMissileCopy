#pragma once
#include "Play.h"
#include "constants.h"

// Here we prototype structs and functions separately
struct Base {
	int* health;
	Play::Point2f* pos;
	bool* isDestroyed;
	int* spriteID;

	// A way to maybe deallocate in case we have more memory leaks
	//~Base() {
	//	delete health;
	//	delete pos;
	//	delete isDestroyed;
	//	delete spriteID;
	//}
};

// todo: put spriteID in parrent class when we have something working
struct MissileBase {
	Base* missileBase[3];
	Base* adjCities[6];
	int currentBaseCount;
	int* currentAmmo;
};

void initMissileBases(MissileBase& missileBase, size_t initialCapacity);
void deallocateData(MissileBase& missileBase);
//void getClosestMissileBase(); // gets x position of mouse, and matches that with missile base
