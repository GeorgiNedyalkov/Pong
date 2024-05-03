#include <stdio.h>
#include <SDL.h>

int main(int argc, char** argv)
{
	int success = SDL_Init(SDL_INIT_VIDEO);
	if (success != 0)
	{
		printf("Could'n initialize SDL: %s", SDL_GetError());
	}

	return 0;
}