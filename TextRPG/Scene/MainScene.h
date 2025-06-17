#pragma once
#include "Scene.h"
#include "../TextPrompt.h"

class MainScene : public Scene
{
public:
	enum class EMainSceneState : uint8
	{
		Default,
		Healer,
		Inventory,
	};

public:
	MainScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	virtual ~MainScene() = default;

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void EnableMainMenu();
	void EnableHealMenu();
	void HandleHealCommand();

private:
	EMainSceneState m_currentSceneState;
};