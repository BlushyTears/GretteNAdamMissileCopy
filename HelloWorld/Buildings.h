#pragma once
#include "Play.h"
#include "constants.h"

//#define NUM_CITIES 2 // Since we know there are always two adjacent cities we can define it up here
//#define NUM_BASES 3 // Since we know there are always two adjacent cities we can define it up here

// Here we prototype structs and functions separately
struct Base {
	int* health;
	Play::Point2D* pos;
	bool* isDestroyed;
	const char* spriteName;
};

// todo: put spriteID in parrent class when we have something working
struct City {
	Base* city;
	int spriteID;
};

// todo: put spriteID in parrent class when we have something working
struct MissileBase {
	Base* missileBase;
	City adjCities[2]; // fixed, since we know missile base will always have two adjacent cities
	int spriteID;
	//int* currentAmmo;
	//const int maxAmmo;
};

MissileBase* initMissileBase(Play::Point2D _pos);
void deallocateData(MissileBase& missileBase);
//void getClosestMissileBase(); // gets x position of mouse, and matches that with missile base
