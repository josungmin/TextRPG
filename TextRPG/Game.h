#pragma once
#include "Screen.h"
#include "Input.h"
#include "TextPrompt.h"


class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

	Game(const Game& rhs) = delete;
	Game(const Game&& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	Game& operator=(Game&& rhs) = delete;

public:
	void Run();

private:
	void Init();
	void Update();
	void Render();

private:
	const uint32 TARGET_FPS = 30;
	const uint32 FRAME_TIME_MS = 1000 / TARGET_FPS;

private:
	Screen m_screen;
	Input m_input;
	TextPrompt m_textPrompt;
};
