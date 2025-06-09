#include "MainScene.h"
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"

MainScene::MainScene(Screen& screen, Input& input)
	:Scene(screen, input), textPrompt(screen, 34, 3)
{
	CurrentSceneState = EMainSceneState::Default;
}

MainScene::~MainScene()
{
}

void MainScene::OnEnter()
{
	screen.Clear();
	textPrompt.Clear();
}

void MainScene::OnExit()
{
	screen.Clear();
	textPrompt.Clear();
}

void MainScene::Update()
{
	textPrompt.Update();

	if (input.HasCommand()) 
	{
		std::wstring cmd = input.GetCommand();

		if (CurrentSceneState == EMainSceneState::Default && cmd == L"Healer")
		{
			textPrompt.Enqueue(L"System : I approach Healer and talk to him.");
			textPrompt.Enqueue(L"Healer : Give me 500 gold and I'll restore your HP!");
			CurrentSceneState = EMainSceneState::Healer;
		}
		else if (CurrentSceneState == EMainSceneState::Default && cmd == L"Inventory")
		{
			PlayerCharacter& player = GameInstance::Instance().GetPlayer();

			auto sword = dynamic_pointer_cast<EquipableItem>(GameInstance::Instance().GetItemTable().CreateItem(L"Sword"));
			if (sword != nullptr)
			{
				player.GetEquipment().Equip(sword, player.GetStats());
			}

			auto armor = dynamic_pointer_cast<EquipableItem>(GameInstance::Instance().GetItemTable().CreateItem(L"Armor"));
			if (sword != nullptr)
			{
				player.GetEquipment().Equip(armor, player.GetStats());
			}
		}
		else if (CurrentSceneState == EMainSceneState::Healer)
		{
			if (cmd == L"Yes") 
			{
				if (GameInstance::Instance().GetPlayer().GetGold().RemoveGold(500))
				{
					GameInstance::Instance().GetPlayer().HealHp(UINT16_MAX);
					textPrompt.Enqueue({ L"Healer : I've restored all your HP!" });
				}
				else 
				{
					textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				}

				CurrentSceneState = EMainSceneState::Default;
			}
			else if (cmd == L"No")
			{
				textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				CurrentSceneState = EMainSceneState::Default;
			}
		}
	}
}

void MainScene::Render()
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
	screen.Write(73, 1, L"<< Village >>");

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
	screen.Write(2, 13, L"Amor: " +(player.GetEquipment().GetArmor() == nullptr ? L"None" : player.GetEquipment().GetArmor()->GetItemName()));
	screen.Write(0, 27, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");

	if (CurrentSceneState == EMainSceneState::Healer)
	{
		screen.Write(2, 28, L"Command List : Yes, No");
	}
	else if (CurrentSceneState == EMainSceneState::Default)
	{
		screen.Write(2, 28, L"Command List : Healer, Shop, Dungeon, Inventory");
	}

	screen.Write(0, 28, L"弛");                                                                                                  screen.Write(126, 28, L"弛");
	screen.Write(0, 29, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	screen.Write(0, 30, L"弛"); screen.Write(2, 30, L"Command > " + input.GetInputBuffer());                                     screen.Write(126, 30, L"弛");
	screen.Write(0, 31, L"戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");

	textPrompt.Render();
}
