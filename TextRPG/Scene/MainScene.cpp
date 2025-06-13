#include "MainScene.h"
#include <string>
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "ShopScene.h"
#include "DungeonScene.h"


MainScene::MainScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3)
{
	m_currentSceneState = EMainSceneState::Default;
}

MainScene::~MainScene()
{
}

void MainScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"시스템 : 마을에 입장합니다.");
	m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
	m_textPrompt.Enqueue(L"시스템 : 1.회복 2.상점 3.인벤토리 4.던전");
}

void MainScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void MainScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand()) 
	{
		const wstring cmd = m_input.GetCommand();

		if (m_currentSceneState == EMainSceneState::Default)
		{
			if (cmd == L"1" || cmd == L"힐러" || cmd == L"1.힐러" || cmd == L"1힐러" || cmd == L"힐")
			{
				m_textPrompt.Enqueue(L"시스템 : 힐러에게 다가가 말을 겁니다.");
				m_textPrompt.Enqueue(L"힐러 : 500골드를 주면 너의 체력을 모두 회복시켜 줄게!");
				m_textPrompt.Enqueue(L"시스템 : 1.수락한다 2.거절한다");
				m_currentSceneState = EMainSceneState::Healer;
			}
			if (cmd == L"2" || cmd == L"상점" || cmd == L"2.상점" || cmd == L"2상점")
			{
				Scene* shopScene = new ShopScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*shopScene);
			}
			if (cmd == L"3" || cmd == L"인벤" || cmd == L"인벤토리" || cmd == L"3.인벤" || cmd == L"3인벤" || cmd == L"3인벤토리" || cmd == L"3.인벤토리")
			{
				m_textPrompt.Enqueue(L"시스템 : '아이템명 장착', '아이템명 해제' 혹은 '취소'를 입력하세요.");
				m_currentSceneState = EMainSceneState::Inventory;
			}
			if (cmd == L"4" || cmd == L"던전" || cmd == L"4던전" || cmd == L"4.던전")
			{
				Scene* dungeonScene = new DungeonScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
			}
		}
		else if (m_currentSceneState == EMainSceneState::Healer)
		{
			if (cmd == L"1" || cmd == L"수락" || cmd == L"수락한다" || cmd == L"1.수락" || cmd == L"1수락" || cmd == L"1수락한다" || cmd == L"1.수락한다")
			{
				PlayerCharacter player = GameInstance::Instance().GetPlayer();

				if (player.GetCurrentHP() == player.GetStats().GetStatValue(EStatType::HP))
				{
					m_textPrompt.Enqueue({ L"힐러 : 너 이미 체력이 다 회복된것 같아..." });
				}
				else if (GameInstance::Instance().GetPlayer().GetGold().RemoveGold(500))
				{
					GameInstance::Instance().GetPlayer().HealHp(UINT16_MAX);
					m_textPrompt.Enqueue({ L"힐러 : 너의 체력을 모두 회복시켰어!" });
				}
				else
				{
					m_textPrompt.Enqueue({ L"힐러 : 너 돈이 부족하구나..." });
				}

				m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
				m_textPrompt.Enqueue(L"시스템 : 1.회복 2.상점 3.인벤토리 4.던전");
				m_currentSceneState = EMainSceneState::Default;
			}
			else if (cmd == L"2" || cmd == L"거절" || cmd == L"거절한다" || cmd == L"1.거절" || cmd == L"1거절" || cmd == L"1거절한다" || cmd == L"1.거절한다")
			{
				m_textPrompt.Enqueue({ L"힐러 : 너 돈이 부족하구나..." });
				m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
				m_textPrompt.Enqueue(L"시스템 : 1.회복 2.상점 3.인벤토리 4.던전");
				m_currentSceneState = EMainSceneState::Default;
			}
		}
		else if (m_currentSceneState == EMainSceneState::Inventory)
		{
			PlayerCharacter& player = GameInstance::Instance().GetPlayer();
			const vector<Item*>& items = player.GetInventory().GetItems();

			if (cmd == L"취소")
			{
				m_currentSceneState = EMainSceneState::Default;
				m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
				m_textPrompt.Enqueue(L"시스템 : 1.회복 2.상점 3.인벤토리 4.던전");
				return;
			}

			for (Item* item : items)
			{
				if (item == nullptr || item->GetType() != EItemType::Equip)
				{
					continue;
				}

				const wstring name = item->GetItemName();
				if (cmd == name + L" 장착")
				{
					EquipableItem* equip = dynamic_cast<EquipableItem*>(item);
					if (equip == nullptr)
					{
						m_textPrompt.Enqueue(L"[오류] : [" + name + L"] 은 장착 가능한 아이템이 아닙니다.");
						continue;
					}

					player.GetEquipment().Equip(equip, player.GetStats());
					m_textPrompt.Enqueue(L"시스템 : [" + name + L"] 을(를) 장착했습니다.");
					m_currentSceneState = EMainSceneState::Default;
					return;
				}
				else if (cmd == name + L" 해제")
				{
					const EquipableItem* equip = dynamic_cast<EquipableItem*>(item);
					if (equip == nullptr)
					{
						m_textPrompt.Enqueue(L"[오류] : [" + name + L"] 은 해제 가능한 아이템이 아닙니다.");
						continue;
					}

					player.GetEquipment().Unequip(equip->GetEquipType(), player.GetStats());
					m_textPrompt.Enqueue(L"시스템 : [" + name + L"] 을(를) 해제했습니다.");
					m_currentSceneState = EMainSceneState::Default;
					return;
				}
				else
				{
					m_textPrompt.Enqueue(L"시스템 : 인식할 수 없는 명령입니다.");
					m_textPrompt.Enqueue(L"'아이템명 장착' 또는 '아이템명 해제'를 입력하거나, '취소'를 입력하세요.");
				}
			}
		}
	}
}

void MainScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"│");
		m_screen.Write(32, y, L"│");
		m_screen.Write(126, y, L"│");
	}

	m_screen.Write(13, 1, L"[ 능력치 ]");
	m_screen.Write(73, 1, L"<< 마을 >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────");
	m_screen.Write(2, 3, L"이름: " + player.GetName());
	m_screen.Write(2, 4, L"정보: " + player.GetDescription());
	m_screen.Write(2, 5, L"레벨: " + to_wstring(player.GetExperience().m_level));
	m_screen.Write(2, 6, L"경험치: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().m_currentExp));
	m_screen.Write(2, 7, L"골드: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"공격력: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"방어력: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"민첩: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"장착 아이템");
	m_screen.Write(2, 14, L"무기: " + (player.GetEquipment().GetWeapon() == nullptr ? L"미장착" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"방어구: " + (player.GetEquipment().GetArmor() == nullptr ? L"미장착" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"인벤토리 ");
	for (int i = 0; i < player.GetInventory().GetItems().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItems()[i]->GetItemName());
	}
	m_screen.Write(0, 29, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 30, L"│"); m_screen.Write(2, 30, L"명령 > " + m_input.GetInputBuffer());                                    
	m_screen.Write(126, 30, L"│");
	m_screen.Write(0, 31, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");

	m_textPrompt.Render();
}
