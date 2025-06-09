#pragma once
#include "Screen.h"
#include "Input.h"

class Game
{
public:
	Game();
	~Game();

public:
	void Run();

private:
	void Init();
	void Update();
	void Render();

private:
	const int targetFPS = 30;
	const int frameTimeMS = 1000 / targetFPS;

private:
	Screen screen;
	Input input;
};

