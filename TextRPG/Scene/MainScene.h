#pragma once
#include "Scene.h"
#include "../TextPrompt.h"

enum class EMainSceneState : uint8_t
{
	Default,
	Healer,
};


class MainScene : public Scene
{
public:
	MainScene(Screen& screen, Input& input);
	virtual ~MainScene() override;

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TextPrompt m_textPrompt;
	EMainSceneState m_currentSceneState;
};

