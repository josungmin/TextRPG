#pragma once
#include "Scene.h"
#include "../TextPrompt.h"

enum class EMainSceneState : uint8
{
	Default,
	Healer,
	Inventory,
};

class MainScene : public Scene
{
public:
	MainScene(Screen& screen, Input& input);
	~MainScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TextPrompt m_textPrompt;
	EMainSceneState m_currentSceneState;
};

