#include <stdio.h>
#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main(int argc, char** argv)
{
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

	bool running = true;
	SDL_Event event;

	while (running)
	{
		// Process Input
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

		// DRAW  the scene
		// Set the render color
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// Clear the back buffer and set the draw color
		SDL_RenderClear(renderer);

		// Swap the front an back buffer
		SDL_RenderPresent(renderer);
	}

	// Shutdown Game
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


