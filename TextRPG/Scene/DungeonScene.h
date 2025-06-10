#pragma once
#include "Scene.h"
#include <memory>

#include "../TextPrompt.h"

class EnemyCharacter;

enum class EDungeonSceneState : uint8_t
{
	Default,
	Combat,
};


class DungeonScene : public Scene
{
public:
	DungeonScene(Screen& screen, Input& input);
	virtual ~DungeonScene() override;

public:
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	TextPrompt textPrompt;
	EDungeonSceneState CurrentSceneState = EDungeonSceneState::Default;

	std::unique_ptr<EnemyCharacter> enemy = nullptr;
};