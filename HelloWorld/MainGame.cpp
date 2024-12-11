#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "constants.h"
#include "GameManager.h"

GameManager gm;

// Note for self. Remember when uploading to change git remote repo to 4th one, because this one is connected to snake
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	gm.setupGame();
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
}

// Todo high level:
// Add explosion effect when missile is deleted (or after, not sure) 
// Add missile chaining
// Add ammo and text under each base
// Separate shoting positions to be from each base based on the x-axis
// Add enemy hailfire when all buildings are destroyed
// 

// Low level things to do that isn't implicitly suggested by the above:
// Add rendering class for drawing and migrate existing relevant code there
// Change missileBaseList to be actually dynamic and not an object
// 
//	-------------------------------------------------------------------------------------------------
// 
// Todo list (things idc about but should be done at some point to simplify code):
// - Put spriteID in parrent class instead

// Here's how to calculate direction and use it
// Play::Vector2D direction = (this->target - this->origin);
// direction.Normalize();
// Play::Vector2D velocity = direction * speed;
// this->position += velocity * deltaTime;

// Endpoint here gives us the tip of the missile, probably where we want to draw the missile itself (A point that varies its color)
//Play::Point2D endPoint = this->origin + direction * distanceTravelled;
//Play::DrawLine(this->origin, endPoint, this->colour);

bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );

	gm.frame(elapsedTime);

	Play::PresentDrawingBuffer();
	return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE);
}

int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

// Idea structure: We want a game based on three bases that shot missiles on asteroids. 

// Each base is a class two adjacent cities that can be destroyed and drawn and has health (just like the missile base except it can't shoot)
// The base can shot a missile at a time which also creates a reticle
// followed by an explosion 

// Also, remove the linked list, because it's slower and doesn't make sense to keep all objects within a linked list.
// It's better to have a bunch of specific lists and through that rely on caching to optimize things.



// Don't remove this because it's frustrating to look up over and over again
//std::string tempString = "Missile count: " + std::to_string(missileList->missileCount);
//const char* myArray = tempString.c_str();
//Play::DrawDebugText({ 300, 400 }, myArray, Play::cBlue, true);