#pragma once
#include "Scene.h"
#include "../TextPrompt.h"
#include "../Item/EquipableItem.h"

class EquipableItem;

enum class EMainSceneState : uint8
{
	Default,
	Healer,
	Inventory,
};

class MainScene : public Scene
{
public:
	MainScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	~MainScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void ShowMainMenu();
	void HandleHealCommand();
	void HandleEquipCommand(const EquipableItem* equipItem);
	void HandleUnequipCommand(const EEquipType equipType);

private:
	EMainSceneState m_currentSceneState;
};