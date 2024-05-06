#include "Paddle.h"

Paddle::Paddle(): 
	mWidth(25.0f), 
	mHeight(150.0f), 
	mDirection(0), 
	mPosition{0.0f, 0.0f},
	mVelocity{0.0f, 300.0f}
{}


void Paddle::Update(float deltaTime)
{
	Vector2 pos = GetPosition();
	Vector2 velocity = GetVelocity();

	if (mDirection != 0)
	{
		pos.y += velocity.y * mDirection * deltaTime;

		if (pos.y <= mHeight / 2.0f)
		{
			pos.y = mHeight / 2.0f;
		}
		else if (pos.y >= WINDOW_HEIGHT - mHeight / 2.0f)
		{
			pos.y = WINDOW_HEIGHT - mHeight / 2.0f;
		}
	}

	SetPosition(pos);
}

void Paddle::ProcessInput(const Uint8* keyboard, int playerIndex)
{
	mDirection = 0;

	if (playerIndex == 0)
	{
		if (keyboard[SDL_SCANCODE_W])
		{
			mDirection -= 1;
		}
		else if (keyboard[SDL_SCANCODE_S])
		{
			mDirection += 1;
		}
	}

	else if (playerIndex == 1)
	{
		if (keyboard[SDL_SCANCODE_UP])
		{
			mDirection -= 1;
		}
		else if (keyboard[SDL_SCANCODE_DOWN])
		{
			mDirection += 1;
		}
	}
}

