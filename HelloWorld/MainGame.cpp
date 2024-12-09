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

// Notes for monday:
// 
// - Calculate direction of the missile
// - Apply velocity to missiles based on starting pos (hardcode this for now) to ending pos
// - Draw missile (Drawline() function) based on trajectory
// - WHen missile hits its target, delete it and maybe make explosion effect
// - The explosion compares radiuses with other missiles and if another entity is within, then that missile also runs an explode function
// - The above loop also checks for nearby cities, which if within radius has their destroyed bool set to true and rubble is drawn instead
// - if all cities and missile bases are destroyed, game is over (maybe add missile rain if time allows)

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