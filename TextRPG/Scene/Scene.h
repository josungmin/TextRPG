#pragma once
#include "../Screen.h"
#include "../Input.h"
#include "../TextPrompt.h"

class Scene
{
public:
	Scene(Screen& screen, Input& input)
		: m_screen(screen), m_input(input)
	{

	}

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	Screen& m_screen;
	Input& m_input;
};