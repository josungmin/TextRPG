#pragma once
#include "Screen.h"
#include "Input.h"
#include "TextPrompt.h"


class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

public:
	void Run();

private:
	void Init();
	void Update();
	void Render();

private:
	const ULONGLONG TARGET_FPS = 30;
	const ULONGLONG FRAME_TIME_MS = 1000 / TARGET_FPS;

private:
	Screen m_screen;
	Input m_input;
	TextPrompt m_textPrompt;
};
