#pragma once
#include "Rendering.h"
#include "Buildings.h"
#include "Missile.h"
#include "constants.h"

class Rendering
{
public:
	void renderStuff(MissileBase& missileBasesList, Missile& missileList, Explosion& explosionList);
};

