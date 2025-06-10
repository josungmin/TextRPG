#pragma once
#include "Scene/SceneManager.h"
#include "Stat/StatDataType.h"
#include "Character/PlayerCharacter.h"
#include "Item/ItemTable.h"

class GameInstance
{
public:
	static GameInstance& Instance()
	{
		static GameInstance instance;
		return instance;
	};

private:
	GameInstance() = default;
	~GameInstance() = default;

public:
	ItemTable& GetItemTable() { return itemTable; }
	PlayerCharacter& GetPlayer() { return player; }
	SceneManager& GetSceneManager() { return sceneManager; }

private:
	ItemTable itemTable;
	PlayerCharacter player{ L"SungMin", L"Hero this game" };
	SceneManager sceneManager;
};

