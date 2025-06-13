#pragma once
#include "Scene.h"
#include "../TextPrompt.h"
#include "../Character/EnemyCharacter.h"
#include "../CombatGameMode.h"

using namespace std;

enum class EDungeonSceneState : uint8
{
	Default,
	Combat,
	ContinueCombat,
};

class DungeonScene : public Scene
{
public:
	DungeonScene(Screen& screen, Input& input);
	~DungeonScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TextPrompt m_textPrompt;
	CombatGameMode m_combatGameMode;

	EnemyCharacter* m_enemy;
	EDungeonSceneState m_currentSceneState = EDungeonSceneState::Default;
};