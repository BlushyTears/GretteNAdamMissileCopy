#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "constants.h"
#include "GameManager.h"

GameManager gm;

// Note for self. Remember when uploading to change git remote repo to 4th one, because this one is connected to snake
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
}

// Todo high level:
// Add ammo count
// Add different shoting locations
// Add enemy missiles plus marker showing their end destination
// Add hellfire when game ends (Called when all building has their boolean isDestroyed set to true) (extra)
// Add tip of missile and make it vary colors (extra)
// Add variying coloring for explosion (extra)
// Remove memory leaks (extra)

// Low level things to do that isn't implicitly suggested by the above:
// When buildings collide with explosion radius it should take damage (should be a very simple 5 lines of code)
// -------------------------------------------------------------------------------------------------

// Endpoint here gives us the tip of the missile, probably where we want to draw the missile itself (A point that varies its color)
// Play::Point2D endPoint = this->origin + direction * distanceTravelled;
// Play::DrawLine(this->origin, endPoint, this->colour);

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

// Don't remove this because it's frustrating to look up over and over again
// std::string tempString = "Missile count: " + std::to_string(missileList->missileCount);
// const char* myArray = tempString.c_str();
// Play::DrawDebugText({ 300, 400 }, myArray, Play::cBlue, true);