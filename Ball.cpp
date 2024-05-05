#include "Ball.h"

Ball::Ball():mWidth(25.0f), mHeight(25.0f), mVelocity{ 300.0f, 100.0f }, mPosition{ 0.0f, 0.0f }
{
}

void Ball::Update(float deltaTime)
{
	Vector2 pos = GetPosition();
	Vector2 velocity = GetVelocity();

	pos.x += velocity.x * deltaTime;
	pos.y += velocity.y * deltaTime;

	SetPosition(pos);
}
