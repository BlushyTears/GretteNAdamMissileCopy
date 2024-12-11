#pragma once
#include "Play.h"

struct MyColor {
	float r, g, b, a;

	MyColor() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {} // def constructor since play.h doesn't include one in its color impl

	MyColor(float red, float green, float blue, float alpha = 1.0f)
		: r(red), g(green), b(blue), a(alpha) {
	}
};

struct Missile {
    Play::Point2f* startingPositions = nullptr;
    Play::Point2f* currentPositions = nullptr;
    Play::Point2f* endingPositions = nullptr;
    MyColor* colours = nullptr;
    float* distancesTravelled = nullptr;
    bool* missilesToBeDestroyed = nullptr;
    size_t missileCount = 0;
    size_t missileCapacity = 0;
};

struct Explosion {
    Play::Point2f* explosionPositions = nullptr;
    int* radiuses = nullptr;
    size_t explosionCount = 0;
    size_t explosionCapacity = 0;
};

//void addMissile(int x, int y); // appends a new missile to arrays without using OOP
void initExplosionList(Explosion& expl, size_t& initialCapacity);
void initMissileList(Missile& missileList, size_t& initialCapacity);
void addMisile(Missile& missileList, Play::Point2f _startingPos, Play::Point2f _endingPos, MyColor _myColor);
void deleteMissile(Missile& missileList, size_t missileIndex);
void cleanUpMissiles(Missile& missileList, Explosion& expl);
void removeExplosion(Explosion& expl, size_t explIndex);

void updateMissilesPositions(Missile& missileList, Explosion& expl, float deltatime);
//void checkChain(Missile& missileList, int i);