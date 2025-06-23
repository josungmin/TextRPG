#include "MainScene.h"
#include <string>
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "../Item/Item.h"
#include "../Item/EquipableItem.h"
#include "ShopScene.h"
#include "InventoryScene.h"
#include "DungeonScene.h"


MainScene::MainScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
{
	m_currentSceneState = EMainSceneState::Default;
}

void MainScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"시스템 : 마을에 입장합니다.");
	EnableMainMenu();
}

void MainScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void MainScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand() == true)
	{
		const wstring cmd = m_input.GetCommand();
		PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

		switch (m_currentSceneState)
		{
			case EMainSceneState::Default:
			{
				if (cmd == L"1" || cmd == L"힐러" || cmd == L"1.힐러")
				{
					m_currentSceneState = EMainSceneState::Healer;
					EnableHealMenu();
				}
				else if (cmd == L"2" || cmd == L"상점" || cmd == L"2.상점")
				{
					Scene* shopScene = new ShopScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*shopScene);
				}
				else if (cmd == L"3" || cmd == L"인벤토리" || cmd == L"3.인벤토리")
				{
					Scene* inventoryScene = new InventoryScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*inventoryScene);
				}
				else if (cmd == L"4" || cmd == L"던전" || cmd == L"4.던전")
				{
					if (player.GetIsDead() == true)
					{
						m_textPrompt.Enqueue(L"시스템 : HP가 부족해 던전에 입장할 수 없습니다.");
						return;
					}

					Scene* dungeonScene = new DungeonScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*dungeonScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"시스템 : 인식할 수 없는 명령입니다. 다시 입력해 주세요.");
				}
				break;
			}
			case EMainSceneState::Healer:
			{
				if (cmd == L"1" || cmd == L"수락" || cmd == L"1.수락")
				{
					HandleHealCommand();
				}
				else if (cmd == L"2" || cmd == L"거절" || cmd == L"2.거절")
				{
					m_textPrompt.Enqueue(L"힐러 : 다음에 또와.");
					EnableMainMenu();
					m_currentSceneState = EMainSceneState::Default;	
				}
				else
				{
					m_textPrompt.Enqueue(L"시스템 : 인식할 수 없는 명령입니다. 다시 입력해 주세요.");
				}
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void MainScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"│");
		m_screen.Write(32, y, L"│");
		m_screen.Write(126, y, L"│");
	}

	m_screen.Write(13, 1, L"[ 능력치 ]");
	m_screen.Write(73, 1, L"<< 인벤토리 >>");

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	m_screen.Write(1, 2, L"────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────");
	m_screen.Write(2, 3, L"이름: " + player.GetName());
	m_screen.Write(2, 4, L"정보: " + player.GetDescription());
	m_screen.Write(2, 5, L"레벨: " + to_wstring(player.GetExperience().level));
	m_screen.Write(2, 6, L"경험치: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().currentExp));
	m_screen.Write(2, 7, L"골드: " + to_wstring(player.GetGold().amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"공격력: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"방어력: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"민첩: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"장착 아이템");
	m_screen.Write(2, 14, L"무기: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon) == nullptr ? L"미장착" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon)->GetItemName())));
	m_screen.Write(2, 15, L"방어구: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Armor) == nullptr ? L"미장착" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::
		Armor)->GetItemName())));
	m_screen.Write(2, 17, L"인벤토리 ");
	const vector<ItemInstance>& itemList = player.GetInventory().GetItemList();
	for (int i = 0; i < itemList.size(); ++i)
	{
		m_screen.Write(2, 18 + i, itemList[i].Get()->GetItemName());
	}
	m_screen.Write(0, 29, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 30, L"│"); m_screen.Write(2, 30, L"명령 > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"│");
	m_screen.Write(0, 31, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");
}

void MainScene::EnableMainMenu()
{
	m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
	m_textPrompt.Enqueue(L"시스템 : 1.회복 2.상점 3.인벤토리 4.던전");
}

void MainScene::EnableHealMenu()
{
	m_textPrompt.Enqueue(L"시스템 : 힐러에게 다가가 말을 겁니다.");
	m_textPrompt.Enqueue(L"힐러 : 500골드를 주면 너의 체력을 모두 회복시켜 줄게!");
	m_textPrompt.Enqueue(L"시스템 : 1.수락 2.거절");
}

void MainScene::HandleHealCommand()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	const uint16 playerMaxHP = player.GetStats().GetStatValue(EStatType::HP);

	if (player.GetCurrentHP() == playerMaxHP)
	{
		m_textPrompt.Enqueue({ L"힐러 : 너 이미 체력이 다 회복된것 같아..." });
	}
	else if (player.GetGold().RemoveGold(500))
	{
		player.HealHp(playerMaxHP);
		m_textPrompt.Enqueue({ L"힐러 : 너의 체력을 모두 회복시켰어!" });
	}
	else
	{
		m_textPrompt.Enqueue({ L"힐러 : 돈이 있어야 회복을 시켜줄 수 있어!" });
	}

	m_currentSceneState = EMainSceneState::Default;
	EnableMainMenu();
}

