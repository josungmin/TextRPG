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

	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
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
				if (cmd == L"1" || cmd == L"����" || cmd == L"1.����")
				{
					m_currentSceneState = EMainSceneState::Healer;
					EnableHealMenu();
				}
				else if (cmd == L"2" || cmd == L"����" || cmd == L"2.����")
				{
					Scene* shopScene = new ShopScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*shopScene);
				}
				else if (cmd == L"3" || cmd == L"�κ��丮" || cmd == L"3.�κ��丮")
				{
					Scene* inventoryScene = new InventoryScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*inventoryScene);
				}
				else if (cmd == L"4" || cmd == L"����" || cmd == L"4.����")
				{
					if (player.GetIsDead() == true)
					{
						m_textPrompt.Enqueue(L"�ý��� : HP�� ������ ������ ������ �� �����ϴ�.");
						return;
					}

					Scene* dungeonScene = new DungeonScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*dungeonScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"�ý��� : �ν��� �� ���� ����Դϴ�. �ٽ� �Է��� �ּ���.");
				}
				break;
			}
			case EMainSceneState::Healer:
			{
				if (cmd == L"1" || cmd == L"����" || cmd == L"1.����")
				{
					HandleHealCommand();
				}
				else if (cmd == L"2" || cmd == L"����" || cmd == L"2.����")
				{
					m_textPrompt.Enqueue(L"���� : ������ �ǿ�.");
					EnableMainMenu();
					m_currentSceneState = EMainSceneState::Default;	
				}
				else
				{
					m_textPrompt.Enqueue(L"�ý��� : �ν��� �� ���� ����Դϴ�. �ٽ� �Է��� �ּ���.");
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
	m_screen.Write(0, 0, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"��");
		m_screen.Write(32, y, L"��");
		m_screen.Write(126, y, L"��");
	}

	m_screen.Write(13, 1, L"[ �ɷ�ġ ]");
	m_screen.Write(73, 1, L"<< �κ��丮 >>");

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	m_screen.Write(1, 2, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(2, 3, L"�̸�: " + player.GetName());
	m_screen.Write(2, 4, L"����: " + player.GetDescription());
	m_screen.Write(2, 5, L"����: " + to_wstring(player.GetExperience().level));
	m_screen.Write(2, 6, L"����ġ: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().currentExp));
	m_screen.Write(2, 7, L"���: " + to_wstring(player.GetGold().amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"���ݷ�: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"����: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"��ø: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"���� ������");
	m_screen.Write(2, 14, L"����: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon) == nullptr ? L"������" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon)->GetItemName())));
	m_screen.Write(2, 15, L"��: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Armor) == nullptr ? L"������" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::
		Armor)->GetItemName())));
	m_screen.Write(2, 17, L"�κ��丮 ");
	const vector<ItemInstance>& itemList = player.GetInventory().GetItemList();
	for (int i = 0; i < itemList.size(); ++i)
	{
		m_screen.Write(2, 18 + i, itemList[i].Get()->GetItemName());
	}
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}

void MainScene::EnableMainMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : � �ൿ�� �Ͻðڽ��ϱ�?");
	m_textPrompt.Enqueue(L"�ý��� : 1.ȸ�� 2.���� 3.�κ��丮 4.����");
}

void MainScene::EnableHealMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : �������� �ٰ��� ���� �̴ϴ�.");
	m_textPrompt.Enqueue(L"���� : 500��带 �ָ� ���� ü���� ��� ȸ������ �ٰ�!");
	m_textPrompt.Enqueue(L"�ý��� : 1.���� 2.����");
}

void MainScene::HandleHealCommand()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	const uint16 playerMaxHP = player.GetStats().GetStatValue(EStatType::HP);

	if (player.GetCurrentHP() == playerMaxHP)
	{
		m_textPrompt.Enqueue({ L"���� : �� �̹� ü���� �� ȸ���Ȱ� ����..." });
	}
	else if (player.GetGold().RemoveGold(500))
	{
		player.HealHp(playerMaxHP);
		m_textPrompt.Enqueue({ L"���� : ���� ü���� ��� ȸ�����׾�!" });
	}
	else
	{
		m_textPrompt.Enqueue({ L"���� : ���� �־�� ȸ���� ������ �� �־�!" });
	}

	m_currentSceneState = EMainSceneState::Default;
	EnableMainMenu();
}

