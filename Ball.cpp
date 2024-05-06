#include "Ball.h"
#include "Math.h"
#include <stdio.h>

Ball::Ball():mWidth(25.0f), mHeight(25.0f), mVelocity{ 300.0f, -100.0f }, mPosition{ 0.0f, 0.0f }
{
}

void Ball::Update(float deltaTime)
{
	Vector2 pos = GetPosition();
	Vector2 velocity = GetVelocity();

	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;

	if (pos.y <= 0)
	{
		velocity.y *= -1;
	}
	else if (pos.y >= WINDOW_HEIGHT - 25)
	{
		velocity.y *= -1;
	}

	SetVelocity(velocity);
	SetPosition(pos);
}

void Ball::SetStartPosition()
{
	SetPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f });
}
