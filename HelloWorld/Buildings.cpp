#include "Buildings.h"
#include "Play.h"
#include "constants.h"

void initMissileBases(MissileBase& missileBase, size_t initialCapacity) {
    float usableWidth = DISPLAY_WIDTH * 2 / 3; // nice way to center multiple objects in center
    float startX = DISPLAY_WIDTH / 6;
    float spacing = usableWidth / (NUM_BASES - 1);
    float citySpacing = usableWidth / (NUM_CITIES - 1);

    missileBase.currentAmmo = new int[initialCapacity]; // fields exclusive to missileBase do not need to be allocated in loop (only assigned)

    // Initialize missile bases
    for (int i = 0; i < NUM_BASES; i++) {
        float xPos = startX + spacing * i;
        missileBase.missileBase[i] = new Base;
        missileBase.missileBase[i]->health = new int[initialCapacity] {100};
        missileBase.missileBase[i]->pos = new Play::Point2D[initialCapacity]{ {xPos, DISPLAY_HEIGHT / 7} };
        missileBase.missileBase[i]->isDestroyed = new bool[initialCapacity] {false};
        missileBase.missileBase[i]->spriteID = new int[initialCapacity] {1};
        missileBase.currentAmmo[i] = 10;
    }

    // Initialize adjacent cities
    for (int i = 0; i < NUM_CITIES; i++) {
        int baseIndex = i % NUM_BASES; 
        float xPos = startX + spacing * baseIndex;
        xPos += (i % 2 == 0) ? 20 : -15;

        missileBase.adjCities[i] = new Base;
        missileBase.adjCities[i]->health = new int[initialCapacity] {50};
        missileBase.adjCities[i]->pos = new Play::Point2D[initialCapacity]{ {xPos, DISPLAY_HEIGHT / 7} };
        missileBase.adjCities[i]->isDestroyed = new bool[initialCapacity] {false};
        missileBase.adjCities[i]->spriteID = new int[initialCapacity] {0};
    }
}

void deallocateData(MissileBase& missileBase) {
    for (int i = 0; i < NUM_BASES; i++) {
        delete[] missileBase.missileBase[i]->health;
        delete[] missileBase.missileBase[i]->pos;
        delete[] missileBase.missileBase[i]->isDestroyed;
        delete[] missileBase.missileBase[i]->spriteID;
    }

    for (int i = 0; i < NUM_CITIES; i++) {
        delete[] missileBase.adjCities[i]->health;
        delete[] missileBase.adjCities[i]->pos;
        delete[] missileBase.adjCities[i]->isDestroyed;
        delete[] missileBase.adjCities[i]->spriteID;
    }
}



