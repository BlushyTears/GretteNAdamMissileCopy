#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "constants.h"
#include "Classes.h"

SnakeHead snake;
Apple* apple;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	apple = new Apple();
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
}

// Called by PlayBuffer every frame (60 times a second!)
int timePassed = 0;
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );

	snake.draw();
	snake.drawChildren();
	apple->draw();

	// just checks length of snake parts excluding head
	std::string tempString = std::to_string(snake.snakeparts);
	const char* charText = tempString.c_str();
	Play::DrawDebugText({ 50, 50 }, charText, Play::cBlue, true);

	snake.handleInput();
	if (timePassed % 6 == 0) {
		snake.move();
	}

	if (snake.isColliding(apple)) {
		snake.addPart(1);
		delete apple;
		apple = new Apple();
	}

	timePassed++;

	Play::PresentDrawingBuffer();
	return Play::KeyDown(Play::KeyboardButton::KEY_ESCAPE);
}

// Gets called once when the player quits the game
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}


