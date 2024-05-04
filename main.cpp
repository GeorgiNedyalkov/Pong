#include <stdio.h>
#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

struct Vector2
{
	float x;
	float y;
};

int main(int argc, char** argv)
{
	// INITIALIZE
	int success = SDL_Init(SDL_INIT_VIDEO);
	if (success != 0)
	{
		printf("Could not initialize SDL: %s", SDL_GetError());
	}

	SDL_Window* window = SDL_CreateWindow("Pong", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (window == NULL)
	{
		printf("Could not create SDL Renderer: %s", SDL_GetError());
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL)
	{
		printf("Could not create an SDL Renderer: %s", SDL_GetError());
	}

	// The number of miliseconds after the Init function
	Uint32 mTicksCount = SDL_GetTicks();

	bool running = true;

	// Define Paddle position and direction
	Vector2 paddlePosition;
	paddlePosition.x = 0;
	paddlePosition.y = WINDOW_HEIGHT / 2.0f;
	int paddleDir;

	// Define Ball position and direction
	Vector2 ballPosition;
	ballPosition.x = WINDOW_WIDTH / 2.0f;
	ballPosition.y = WINDOW_HEIGHT / 2.0f;
	int ballDir;

	// PROCESS INPUT
	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			}
		}

		const Uint8* keyboard = SDL_GetKeyboardState(NULL);

		if (keyboard[SDL_SCANCODE_ESCAPE])
		{
			running = false;
		}

		paddleDir = 0;
		if (keyboard[SDL_SCANCODE_W])
		{
			paddleDir -= 1;
		}
		else if (keyboard[SDL_SCANCODE_S])
		{
			paddleDir += 1;
		}

		// UPDATE GAME

		// Calculate deltaTime and update the mTicksCount
		float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
		mTicksCount = SDL_GetTicks();

		if (paddleDir != 0)
		{
			paddlePosition.y += paddleDir * 300.0f * deltaTime;
		}

		// DRAW SCENE 
		// Set the render color
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// Clear the back buffer and set the draw color
		SDL_RenderClear(renderer);

		// Set the draw color to white to draw actors
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// Draw the first paddle with a width of 25 pixels and height of 150 pixels
		SDL_Rect paddle{ 
			static_cast<int>(paddlePosition.x),
			static_cast<int>(paddlePosition.y - (150 / 2.0f)),
			25,
			150
		};

		SDL_RenderFillRect(renderer, &paddle);

		// Swap the front an back buffer
		SDL_RenderPresent(renderer);
	}

	// Shutdown Game
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


