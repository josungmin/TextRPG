#pragma once
#include "Screen.h"
#include "Input.h"
#include "TextPrompt.h"

constexpr DWORD TARGET_FPS = 30;
constexpr DWORD FRAME_TIME_MS = 1000 / TARGET_FPS;

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
	Screen m_screen;
	Input m_input;
	TextPrompt m_textPrompt;
};
