#pragma once
#include "Math.h"
#include "SDL.h"

class Ball
{
public:
	Ball();

	void Update(float deltaTime);

	Vector2 GetPosition() const { return mPosition; }
	void SetPosition(Vector2 position) { mPosition = position; }
	Vector2 GetVelocity() const { return mVelocity; }
	void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

	void SetStartPosition();

	float mWidth;
	float mHeight;
	Vector2 mPosition;
	Vector2 mVelocity;
};

