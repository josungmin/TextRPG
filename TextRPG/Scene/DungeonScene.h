#pragma once
#include "Scene.h"
#include "../TextPrompt.h"
#include "../Character/EnemyCharacter.h"
#include "../CombatGameMode.h"

using namespace std;

class DungeonScene : public Scene
{
public:
	enum class EDungeonSceneState : uint8
	{
		Default,
		Combat,
		ContinueCombat,
	};

public:
	DungeonScene(Screen& screen, Input& input, TextPrompt& textPrompt);
	virtual ~DungeonScene();

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	CombatGameMode m_combatGameMode;
	EnemyCharacter* m_enemy;
	EDungeonSceneState m_currentSceneState = EDungeonSceneState::Default;
};