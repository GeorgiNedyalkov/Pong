#pragma once
#include "Math.h"
#include "SDL.h"

class Paddle
{
public:
	Paddle();

	void Update(float deltaTime);
	void ProcessInput(const Uint8* keyboard, int playerIndex);

	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(Vector2 position) { mPosition = position; }
	Vector2 GetVelocity() const { return mVelocity; }
	int GetDirection() const { return mDirection; }

	float const mWidth;
	float const mHeight;
	Vector2 mPosition;
	Vector2 mVelocity;
	int mDirection;
};

