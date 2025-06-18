#pragma once
#include "Scene.h"

class InventoryScene : public Scene
{
public:
	InventoryScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	virtual ~InventoryScene() = default;

public:
	enum class EInventorySceneState : uint8
	{
		Default,
		Equip,
		Unequip,
	};

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	void EnableInventoryMenu();
	void EnableEquipMenu();
	void EnableUnequipMenu();
	void HandleEquipCommand(const wstring& cmd);
	void HandleUnequipCommand(const wstring& cmd);

private:
	EInventorySceneState m_currentSceneState;
};