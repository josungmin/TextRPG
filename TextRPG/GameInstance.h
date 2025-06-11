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
		static GameInstance m_instance;
		return m_instance;
	};

public:
	~GameInstance() = default;

private:
	GameInstance() = default;

public:
	ItemTable& GetItemTable() { return m_itemTable; }
	PlayerCharacter& GetPlayer() { return m_player; }
	SceneManager& GetSceneManager() { return m_sceneManager; }

private:
	ItemTable m_itemTable;
	PlayerCharacter m_player{ L"SungMin", L"Hero this game" };
	SceneManager m_sceneManager;
};

