#pragma once
#include "Screen.h"
#include "Input.h"
#include "TextPrompt.h"

class Game
{
public:
	Game();
	~Game() = default;

public:
	void Run();

private:
	void Init();
	void Update();
	void Render();

private:
	const int TARGET_FPS = 30;
	const int FRAME_TIME_MS = 1000 / TARGET_FPS;

private:
	Screen m_screen;
	Input m_input;
	TextPrompt m_textPrompt;
};
