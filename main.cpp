#include <stdio.h>
#include <SDL.h>
#include "Ball.h"
#include "Math.h"
#include "Paddle.h"

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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Could not create an SDL Renderer: %s", SDL_GetError());
	}

	bool running = true;
	Uint32 mTicksCount = SDL_GetTicks();

	Ball ball;
	ball.SetStartPosition();
	Paddle paddle1;
	paddle1.SetPosition({ 0.0f, WINDOW_HEIGHT / 2.0f });
	Paddle paddle2;
	paddle2.SetPosition({WINDOW_WIDTH - paddle2.mWidth, WINDOW_HEIGHT / 2.0f});

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

		paddle1.ProcessInput(keyboard, 0);
		paddle2.ProcessInput(keyboard, 1);

		// UPDATE GAME

		// Calculate deltaTime and update the mTicksCount
		float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
		mTicksCount = SDL_GetTicks();

		paddle1.Update(deltaTime);
		paddle2.Update(deltaTime);
		ball.Update(deltaTime);

		Vector2 paddlePosition = paddle1.GetPosition();
		Vector2 paddlePosition2 = paddle2.GetPosition();

		float diff = paddlePosition.y - ball.mPosition.y;
		diff = (diff > 0) ? diff : -diff;

		float diff2 = paddlePosition2.y - ball.mPosition.y;
		diff2 = (diff2 > 0) ? diff2 : -diff2;

		if (diff < (150 / 2.0f) + 25 && ball.mPosition.x < 25.0f)
		{
			ball.mVelocity.x *= -1;
		} 
		else if (diff2 < (150 / 2.0f) + 25 && ball.mPosition.x > WINDOW_WIDTH - 50)
		{
			ball.mVelocity.x *= -1;
		}	
		else if (ball.GetPosition().x < 0)
		{
			printf("Player 2 scores! \n");
			ball.mVelocity.x *= -1;
			ball.SetStartPosition();
		}
		else if (ball.GetPosition().x > WINDOW_WIDTH - 25)
		{
			printf("Player 1 scores! \n");
			ball.mVelocity.x *= -1;
			ball.SetStartPosition();
		}
	
		// DRAW SCENE 
		// Set the render color
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		// Clear the back buffer and set the draw color
		SDL_RenderClear(renderer);

		// Set the draw color to white to draw actors
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


		SDL_Rect paddle1Rect{
				static_cast<int>(paddle1.GetPosition().x),
				static_cast<int>(paddle1.GetPosition().y - (paddle1.mHeight / 2.0f)),
				static_cast<int>(paddle1.mWidth),
				static_cast<int>(paddle1.mHeight),
		};
		SDL_RenderFillRect(renderer, &paddle1Rect);

		SDL_Rect paddle2Rect{
				static_cast<int>(paddle2.GetPosition().x),
				static_cast<int>(paddle2.GetPosition().y - (paddle2.mHeight / 2.0f)),
				static_cast<int>(paddle2.mWidth),
				static_cast<int>(paddle2.mHeight),
		};
		SDL_RenderFillRect(renderer, &paddle2Rect);

		SDL_Rect ballRect{
			static_cast<int>(ball.GetPosition().x),
			static_cast<int>(ball.GetPosition().y),
			static_cast<int>(ball.mWidth),
			static_cast<int>(ball.mHeight)
		};
		SDL_RenderFillRect(renderer, &ballRect);

		// Swap the front an back buffer
		SDL_RenderPresent(renderer);
	}

	// Shutdown Game
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}


