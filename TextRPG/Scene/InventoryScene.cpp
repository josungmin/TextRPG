#include "InventoryScene.h"
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "MainScene.h"

InventoryScene::InventoryScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
{
	m_currentScene = EInventorySceneState::Default;
}

void InventoryScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ���ϴ�.");
	EnableInventoryMenu();
}

void InventoryScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void InventoryScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand() == true)
	{
		const wstring cmd = m_input.GetCommand();

		switch (m_currentScene)
		{
			case InventoryScene::EInventorySceneState::Default:
			{
				if (cmd == L"1" || cmd == L"����" || cmd == L"����������" || cmd == L"1.����������")
				{
					EnableEquipMenu();
					m_currentScene = EInventorySceneState::Equip;
				}
				else if (cmd == L"2" || cmd == L"����" || cmd == L"����������" || cmd == L"1.����������")
				{
					EnableUnequipMenu();
					m_currentScene = EInventorySceneState::Unequip;
				}
				else if (cmd == L"3" || cmd == L"������")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"�ý��� : �ν��� �� ���� ����Դϴ�. �ٽ� �Է��� �ּ���.");
				}
				break;
			}
			case InventoryScene::EInventorySceneState::Equip:
			{
				HandleEquipCommand(cmd);
				break;
			}
			case InventoryScene::EInventorySceneState::Unequip:
			{
				HandleUnequipCommand(cmd);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void InventoryScene::Render()
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

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(2, 3, L"�̸�: " + player.GetName());
	m_screen.Write(2, 4, L"����: " + player.GetDescription());
	m_screen.Write(2, 5, L"����: " + to_wstring(player.GetExperience().m_level));
	m_screen.Write(2, 6, L"����ġ: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().m_currentExp));
	m_screen.Write(2, 7, L"���: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"���ݷ�: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"����: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"��ø: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"���� ������");
	m_screen.Write(2, 14, L"����: " + (player.GetEquipment().GetWeapon() == nullptr ? L"������" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"��: " + (player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"�κ��丮 ");
	for (int i = 0; i < player.GetInventory().GetItemList().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItemList()[i]->GetItemName());
	}
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}

void InventoryScene::EnableInventoryMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : � �ൿ�� �Ͻðڽ��ϱ�?");
	m_textPrompt.Enqueue(L"�ý��� : 1.������ ���� 2.������ ���� 3.������");
}

void InventoryScene::EnableEquipMenu()
{	
	const vector<Item*>& inventoryItems = GameInstance::Instance().GetPlayer().GetInventory().GetItemList();

	if (inventoryItems.size() == 0)
	{
		m_textPrompt.Enqueue(L"�ý��� : ������ �������� �������� �ʽ��ϴ�.");
		EnableInventoryMenu();
		m_currentScene = EInventorySceneState::Default;
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : � �������� [����] �Ͻðڽ��ϱ�? ��ȣ�� �Է����ּ���.");
	for (uint8 i = 0; i < inventoryItems.size(); i++)
	{
		m_textPrompt.Enqueue(L"�κ��丮 : [" + to_wstring(i) + L"] " + inventoryItems[i]->GetItemName());
	}
}

void InventoryScene::EnableUnequipMenu()
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();

	m_textPrompt.Enqueue(L"�ý��� : � �������� [����] �Ͻðڽ��ϱ�? ��ȣ�� �Է����ּ���.");
	m_textPrompt.Enqueue(L"�κ��丮 : [0]" + (equipment.GetWeapon() == nullptr ? L"�������" : equipment.GetWeapon()->GetItemName()));
	m_textPrompt.Enqueue(L"�κ��丮 : [1]" + (equipment.GetArmor() == nullptr ? L"�������" : equipment.GetArmor()->GetItemName()));
}

void InventoryScene::HandleEquipCommand(const wstring& cmd)
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();
	Inventory& inventory = player.GetInventory();
	StatContainer& stats = player.GetStats();

	const uint8 index = static_cast<uint8>(stoi(cmd));
	if (index > inventory.GetItemList().size())
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �߸��� ��ȣ�� �Է��߽��ϴ�." });
		return;
	}

	const EquipableItem* targetItem = dynamic_cast<EquipableItem*>(inventory.GetItemList()[index]);
	if (targetItem == nullptr)
	{
		m_textPrompt.Enqueue({ L"�ý��� : ������ �� �ִ� �������� �ƴմϴ�." });
		return;
	}
		
	if (equipment.IsEquiped(targetItem->GetEquipType()) == true)
	{
		if (inventory.IsFull() == true)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			m_textPrompt.Enqueue({ L"[�ý���] : �κ��丮 ������ �����մϴ�." });
			return;
		}

		const EquipableItem* unequipItem = dynamic_cast<EquipableItem*>(equipment.GetWeapon()->Clone());
		if (unequipItem == nullptr)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			delete unequipItem;
			return;
		}

		if (inventory.AddItem(unequipItem) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			delete unequipItem;
			return;
		}

		delete unequipItem;
		return;
	}

	if (inventory.RemoveItem(targetItem->GetItemName()) == false)
	{
		m_textPrompt.Enqueue({ L"[����] : ���ο� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
		return;
	}

	if (equipment.Equip(targetItem, stats) == false)
	{
		m_textPrompt.Enqueue({ L"[����] : ���ο� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + targetItem->GetItemName() + L"] ��(��) �����߽��ϴ�.");

	EnableInventoryMenu();
	m_currentScene = EInventorySceneState::Default;
	return;
}

void InventoryScene::HandleUnequipCommand(const wstring& cmd)
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();
	Inventory& inventory = player.GetInventory();
	StatContainer& stats = player.GetStats();

	if (inventory.IsFull())
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �κ��丮 ������ �����մϴ�." });
		EnableInventoryMenu();
		m_currentScene = EInventorySceneState::Default;
	}

	const uint8 index = static_cast<uint8>(stoi(cmd));
	if (index == 0)
	{
		const EquipableItem* unequipedItem = equipment.GetWeapon();

		if (inventory.AddItem(unequipedItem) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			return;
		}

		if (equipment.Unequip(unequipedItem->GetEquipType(), stats) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			return;
		}

		m_textPrompt.Enqueue(L"�ý��� : [" + unequipedItem->GetItemName() + L"] ��(��) �����߽��ϴ�.");

	}
	else if (index == 1)
	{
		const EquipableItem* unequipedItem = equipment.GetArmor();

		if (inventory.AddItem(unequipedItem) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			return;
		}

		if (equipment.Unequip(unequipedItem->GetEquipType(), stats) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : ���� �������� �����ϴµ� ������ �߻��߽��ϴ�." });
			return;
		}

		m_textPrompt.Enqueue(L"�ý��� : [" + unequipedItem->GetItemName() + L"] ��(��) �����߽��ϴ�.");

		delete unequipedItem;
	}
	else
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �߸��� ��ȣ�� �Է��߽��ϴ�." });
		return;
	}

	EnableInventoryMenu();
	m_currentScene = EInventorySceneState::Default;
	return;
}
