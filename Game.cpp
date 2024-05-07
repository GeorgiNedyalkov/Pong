#include <stdio.h>
#include "Math.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"

Game::Game(): mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0)
{
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Could not initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Pong", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (mWindow == NULL)
	{
		SDL_Log("Could not create SDL Renderer: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == NULL)
	{
		SDL_Log("Could not create an SDL Renderer: %s", SDL_GetError());
		return false;
	}

	mBall = new Ball();
	mBall->SetStartPosition();
	mPaddle1 = new Paddle();
	mPaddle1->SetPosition({ 0.0f, WINDOW_HEIGHT / 2.0f });
	mPaddle2 = new Paddle();
	mPaddle2->SetPosition({WINDOW_WIDTH - mPaddle2->mWidth, WINDOW_HEIGHT / 2.0f});
	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if (keyboard[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddle1->ProcessInput(keyboard, 0);
	mPaddle2->ProcessInput(keyboard, 1);
}

void Game::CheckCollisions(Paddle* paddle)
{
	Vector2 paddlePos = paddle->GetPosition();
	Vector2 ballPos = mBall->GetPosition();
	float diff = paddlePos.y - mBall->mPosition.y;
	diff = (diff > 0) ? diff : -diff;

}

void Game::Update()
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();

	mPaddle1->Update(deltaTime);
	mPaddle2->Update(deltaTime);
	mBall->Update(deltaTime);

	Vector2 paddlePosition = mPaddle1->GetPosition();
	Vector2 paddlePosition2 = mPaddle2->GetPosition();

	float diff = paddlePosition.y - mBall->mPosition.y;
	diff = (diff > 0) ? diff : -diff;

	float diff2 = paddlePosition2.y - mBall->mPosition.y;
	diff2 = (diff2 > 0) ? diff2 : -diff2;

	if (diff < (150 / 2.0f) + 25 && mBall->mPosition.x < 25.0f)
	{
		mBall->mVelocity.x *= -1;
	}
	else if (diff2 < (150 / 2.0f) + 25 && mBall->mPosition.x > WINDOW_WIDTH - 50)
	{
		mBall->mVelocity.x *= -1;
	}
	else if (mBall->GetPosition().x < 0)
	{
		printf("Player 2 scores! \n");
		mBall->mVelocity.x *= -1;
		mBall->SetStartPosition();
	}
	else if (mBall->GetPosition().x > WINDOW_WIDTH - 25)
	{
		printf("Player 1 scores! \n");
		mBall->mVelocity.x *= -1;
		mBall->SetStartPosition();
	}
}

void Game::GenerateOutput()
{
	// Set the render color
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);

	// Clear the back buffer and set the draw color
	SDL_RenderClear(mRenderer);

	// Set the draw color to black to draw actors
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

	SDL_Rect paddleRect1{
			static_cast<int>(mPaddle1->GetPosition().x),
			static_cast<int>(mPaddle1->GetPosition().y - (mPaddle1->mHeight / 2.0f)),
			static_cast<int>(mPaddle1->mWidth),
			static_cast<int>(mPaddle1->mHeight),
	};
	SDL_RenderFillRect(mRenderer, &paddleRect1);

	SDL_Rect paddleRect2{
			static_cast<int>(mPaddle2->GetPosition().x),
			static_cast<int>(mPaddle2->GetPosition().y - (mPaddle2->mHeight / 2.0f)),
			static_cast<int>(mPaddle2->mWidth),
			static_cast<int>(mPaddle2->mHeight),
	};
	SDL_RenderFillRect(mRenderer, &paddleRect2);

	SDL_Rect ballRect{
		static_cast<int>(mBall->GetPosition().x),
		static_cast<int>(mBall->GetPosition().y),
		static_cast<int>(mBall->mWidth),
		static_cast<int>(mBall->mHeight)
	};
	SDL_RenderFillRect(mRenderer, &ballRect);

	// Swap the front an back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	delete mBall;
	delete mPaddle1;
	delete mPaddle2;
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
