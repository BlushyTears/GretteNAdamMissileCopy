#pragma once
#include "Play.h"

// rewrite this later (also, we make our own color since Play.h doesnt have a defualt constructor)
struct MyColor {
	float r, g, b, a;

	MyColor() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {} // def constructor

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
    size_t missileCount = 0;
    size_t missileCapacity = 0;
};

//void addMissile(int x, int y); // appends a new missile to arrays without using OOP
void initMissileList(Missile& missileList, size_t& initialCapacity);
void addMisile(Missile& missileList, Play::Point2f _startingPos, Play::Point2f _endingPos, MyColor _myColor);
void deleteMissile(Missile& missileList, size_t missileIndex);
void updateMissilesPositions(Missile& missileList, float deltatime);
void cleanUpMissiles(Missile& missileList);