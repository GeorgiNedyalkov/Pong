#include <stdio.h>
#include <SDL.h>
#include "Math.h"
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
