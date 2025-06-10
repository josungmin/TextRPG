#include "DungeonScene.h"
#include "../GameInstance.h"
//#include "../Stat/StatDataType.h"
#include "../Character/EnemyCharacter.h"
#include "MainScene.h"

DungeonScene::DungeonScene(Screen& screen, Input& input)
	:Scene(screen, input), textPrompt(screen, 34, 3), enemy(nullptr)
{
	CurrentSceneState = EDungeonSceneState::Default;
}

DungeonScene::~DungeonScene()
{

}

void DungeonScene::OnEnter()
{
	screen.Clear();
	textPrompt.Clear();

	StatContainer enemyStats;
	enemyStats.stats[EStatType::HP].baseValue = 50;
	enemyStats.stats[EStatType::AttackPower].baseValue = 10;
	enemyStats.stats[EStatType::Defence].baseValue = 5;
	enemyStats.stats[EStatType::Agility].baseValue = 5;

	enemy = std::make_unique<EnemyCharacter>(L"Goblin", L"Goblin Soldier", enemyStats);

	textPrompt.Enqueue(L"System : You are entering a dungeon.");
	textPrompt.Enqueue(L"System : In the dungeon you meet a monster.");
}

void DungeonScene::OnExit()
{
	screen.Clear();
	textPrompt.Clear();
}

void DungeonScene::Update()
{
	textPrompt.Update();

	if (input.HasCommand())
	{
		std::wstring cmd = input.GetCommand();

		if (CurrentSceneState == EDungeonSceneState::Default)
		{
			if (cmd == L"Combat")
			{
				textPrompt.Enqueue(L"System : The battle begins.");
			}
			else if (cmd == L"Runaway")
			{
				textPrompt.Enqueue(L"System : You run away from the enemy, but are attacked and your HP decreases.");
				GameInstance::Instance().GetSceneManager().ChangeScene(make_unique<MainScene>(screen, input));
			}
		}
		else if (CurrentSceneState == EDungeonSceneState::Combat)
		{
			
		}
	}
}

void DungeonScene::Render()
{
	// Frame
	screen.Write(0, 0, L"忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

	for (int y = 1; y <= 26; ++y)
	{
		screen.Write(0, y, L"弛");
		screen.Write(32, y, L"弛");
		screen.Write(126, y, L"弛");
	}

	screen.Write(13, 1, L"[ Stat ]");
	screen.Write(73, 1, L"<< Dungeon >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	screen.Write(1, 2, L"式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	screen.Write(2, 3, L"Name: " + player.GetName());
	screen.Write(2, 4, L"Info: " + player.GetDescription());
	screen.Write(2, 5, L"Gold: " + to_wstring(player.GetGold().amount));
	screen.Write(2, 6, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	screen.Write(2, 7, L"AttackPower: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	screen.Write(2, 8, L"Defence: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	screen.Write(2, 9, L"Agility: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	screen.Write(2, 11, L"Equipment");
	screen.Write(2, 12, L"Weapon: " + (player.GetEquipment().GetWeapon() == nullptr ? L"None" : player.GetEquipment().GetWeapon()->GetItemName()));
	screen.Write(2, 13, L"Amor: " + (player.GetEquipment().GetArmor() == nullptr ? L"None" : player.GetEquipment().GetArmor()->GetItemName()));
	screen.Write(0, 27, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");

	if (CurrentSceneState == EDungeonSceneState::Default)
	{
		screen.Write(2, 28, L"Command List : Combat, Runaway");
	}

	screen.Write(0, 28, L"弛");                                                                                                  screen.Write(126, 28, L"弛");
	screen.Write(0, 29, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	screen.Write(0, 30, L"弛"); screen.Write(2, 30, L"Command > " + input.GetInputBuffer());                                     screen.Write(126, 30, L"弛");
	screen.Write(0, 31, L"戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

	textPrompt.Render();
}
