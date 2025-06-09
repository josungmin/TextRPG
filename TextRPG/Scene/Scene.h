#pragma once
#include "../Screen.h"
#include "../Input.h"

class Scene
{
public:
	Scene(Screen& screen, Input& input) : screen(screen), input(input) { }
	virtual ~Scene() { }

	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	Screen& screen;
	Input& input;
};