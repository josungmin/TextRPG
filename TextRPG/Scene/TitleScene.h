#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene(Screen& screen, Input& input, TextPrompt& textPrompt);

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;
};