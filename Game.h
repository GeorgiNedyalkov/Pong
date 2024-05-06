#pragma once
#include "SDL.h"

class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	bool mIsRunning;
	Uint32 mTicksCount;

	class Ball* mBall;
	class Paddle* mPaddle1;
	class Paddle* mPaddle2;
};

