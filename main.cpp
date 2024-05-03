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
		printf("Could not create SDL Window: %s", SDL_GetError());
	}

	bool running = true;
	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}