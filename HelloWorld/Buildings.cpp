#include "Buildings.h"
#include "Play.h"
#include "constants.h"

MissileBase* initMissileBase(Play::Point2D _pos) {
	MissileBase* missileBase = new MissileBase;

	missileBase->missileBase = new Base;
	missileBase->missileBase->health = new int[1] {100};
	missileBase->missileBase->pos = new Play::Point2D[1] {_pos};
	missileBase->missileBase->isDestroyed = new bool[1] {false};

	missileBase->spriteID = 1;

	for (int i = 0; i < NUM_CITIES; i++) {
		missileBase->adjCities[i].city = new Base;
		missileBase->adjCities[i].city->health = new int[1] {50};
		missileBase->adjCities[i].city->isDestroyed = new bool[1] {false};

		missileBase->adjCities[i].spriteID = 0;
	}
	return missileBase;
}

// We delete in backwards order since they are composed of each other
// I guess it's a form of linked list, which I was trying to avoid using
void deallocateData(MissileBase& missileBase) {
	for (int i = 0; i < NUM_CITIES; i++) {
		delete[] missileBase.adjCities[i].city->health;
		delete[] missileBase.adjCities[i].city->isDestroyed;

		// We delete city, when its components have been deleted
		delete[] missileBase.adjCities[i].city;
	}

	delete[] missileBase.missileBase->health;
	delete[] missileBase.missileBase->isDestroyed;
	delete[] missileBase.missileBase;
}

