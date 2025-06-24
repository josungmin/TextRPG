#include "InventoryScene.h"
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "MainScene.h"

InventoryScene::InventoryScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
{
	m_currentSceneState = EInventorySceneState::Default;
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

		switch (m_currentSceneState)
		{
			case InventoryScene::EInventorySceneState::Default:
			{
				if (cmd == L"1" || cmd == L"����" || cmd == L"����������" || cmd == L"1.����������")
				{
					m_currentSceneState = EInventorySceneState::Equip;
					EnableEquipMenu();
				}
				else if (cmd == L"2" || cmd == L"����" || cmd == L"����������" || cmd == L"1.����������")
				{
					m_currentSceneState = EInventorySceneState::Unequip;
					EnableUnequipMenu();
				}
				else if (cmd == L"3" || cmd == L"������")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"�ý��� : �ν��� �� ���� ����Դϴ�. �ٽ� �Է��� �ּ���.");
				}
				break;
			}
			case InventoryScene::EInventorySceneState::Equip:
			{
				if (cmd == L"���")
				{
					EnableInventoryMenu();
					m_currentSceneState = EInventorySceneState::Default;
					return;
				}

				const int index = std::stoi(cmd);
				if (index < 0 || GameInstance::GetInstance().GetPlayer().GetInventory().GetItemList().size() < index)
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					EnableInventoryMenu();
					m_currentSceneState = EInventorySceneState::Default;
					return;
				}

				HandleEquipCommand(index);
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

void InventoryScene::EnableInventoryMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : � �ൿ�� �Ͻðڽ��ϱ�?");
	m_textPrompt.Enqueue(L"�ý��� : 1.������ ���� 2.������ ���� 3.������");
}

void InventoryScene::EnableEquipMenu()
{	
	const vector<ItemInstance>& itemList = GameInstance::GetInstance().GetPlayer().GetInventory().GetItemList();

	if (itemList.empty() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : ������ �������� �������� �ʽ��ϴ�.");
		EnableInventoryMenu();
		m_currentSceneState = EInventorySceneState::Default;
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : � �������� [����] �Ͻðڽ��ϱ�? ��ȣ�� �Է����ּ���.");

	for (uint8 i = 0; i < itemList.size(); ++i)
	{
		m_textPrompt.Enqueue(L"�κ��丮 : [" + to_wstring(i) + L"] " + itemList[i].Get()->GetItemName());
	}
}

void InventoryScene::EnableUnequipMenu()
{
	Equipment& equipment = GameInstance::GetInstance().GetPlayer().GetEquipment();
	const EquipableItem* weapon = equipment.GetEquipedItem(EquipableItem::EEquipType::Weapon);
	const EquipableItem* armor = equipment.GetEquipedItem(EquipableItem::EEquipType::Armor);

	m_textPrompt.Enqueue(L"�ý��� : � �������� [����] �Ͻðڽ��ϱ�? ��ȣ�� �Է����ּ���.");
	m_textPrompt.Enqueue(L"�κ��丮 : [0] " + (weapon == nullptr ? L"�������" : weapon->GetItemName()));
	m_textPrompt.Enqueue(L"�κ��丮 : [1] " + (armor == nullptr ? L"�������" : armor->GetItemName()));
}

void InventoryScene::HandleEquipCommand(const uint8 equipItemIndex)
{
	Inventory& inventory = GameInstance::GetInstance().GetPlayer().GetInventory();
	if (equipItemIndex < 0 || equipItemIndex >= static_cast<uint8>(inventory.GetItemList().size()))
	{
		m_textPrompt.Enqueue(L"[����] : �ε��� ������ �ʰ��߽��ϴ�. �ٽ� �Է����ּ���.");
		return;
	}

	const EquipableItem* selectedItem = inventory.GetItemList()[equipItemIndex].Get<EquipableItem>();
	if (selectedItem == nullptr)
	{
		m_textPrompt.Enqueue({ L"[����] : �������� �������� �ʽ��ϴ�." });
		return;
	}

	Equipment& equipment = GameInstance::GetInstance().GetPlayer().GetEquipment();
	StatContainer& statContainer = GameInstance::GetInstance().GetPlayer().GetStats();

	const EquipableItem::EEquipType selectedEquipType = selectedItem->GetEquipType();
	if (equipment.IsEquiped(selectedEquipType) == true)
	{
		ItemInstance unequipItemInstance = equipment.UnequipItem(selectedEquipType, statContainer);
		if (unequipItemInstance.IsValid() == false)
		{
			m_textPrompt.Enqueue({ L"[����] : �κ��丮���� ������ �߰��� �����߽��ϴ�." });
			m_textPrompt.Enqueue({ L"[����] : unequipItemInstance is not valid" }); // TODO : �ӽ� �ڵ�
			return;
		}
		
		if (inventory.AddItem(move(unequipItemInstance)) == false)
		{
			m_textPrompt.Enqueue({ L"[����] : �κ��丮���� ������ �߰��� �����߽��ϴ�." });
			return;
		}
	}

	const wstring& itemName = selectedItem->GetItemName();
	ItemInstance equipItemInstance = inventory.RemoveItem(itemName);
	if (equipItemInstance.IsValid() == false)
	{
		m_textPrompt.Enqueue({ L"[����] : �κ��丮���� ������ �߰��� �����߽��ϴ�." });
		m_textPrompt.Enqueue({ L"[����] : equipItemInstance is not valid" }); // TODO : �ӽ� �ڵ�
		return;
	}

	if (equipment.EquipItem(move(equipItemInstance), statContainer) == false)
	{
		m_textPrompt.Enqueue({ L"[����] : ������ ������ �����߽��ϴ�." });
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + itemName + L"] ��(��) �����߽��ϴ�.");
	EnableInventoryMenu();
	m_currentSceneState = EInventorySceneState::Default;
}

// TODO: ���� �ʿ� - ������ ������ �ε��� ���� �ʰ� ��µ�
void InventoryScene::HandleUnequipCommand(const wstring& cmd)
{
	Inventory& inventory = GameInstance::GetInstance().GetPlayer().GetInventory();
	Equipment& equipment = GameInstance::GetInstance().GetPlayer().GetEquipment();
	StatContainer& statContainer = GameInstance::GetInstance().GetPlayer().GetStats();

	if (inventory.IsFull())
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �κ��丮 ������ �����մϴ�." });
		EnableInventoryMenu();
		m_currentSceneState = EInventorySceneState::Default;
	}

	const uint8 index = static_cast<uint8>(stoi(cmd)) - 1;
	if (index <= 0 || index >= static_cast<uint8>(EquipableItem::EEquipType::Max))
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 �ε��� ������ �ʰ��߽��ϴ�. �ٽ� �Է����ּ���.");
		return;
	}

	const EquipableItem::EEquipType selectedEquipType = static_cast<EquipableItem::EEquipType>(index);

	ItemInstance unequipItemInstance = equipment.UnequipItem(selectedEquipType, statContainer);
	if (unequipItemInstance.IsValid() == false)
	{
		m_textPrompt.Enqueue({ L"[����] : �κ��丮���� ������ �߰��� �����߽��ϴ�." });
		m_textPrompt.Enqueue({ L"[����] : unequipItemInstance is not valid" }); // TODO : �ӽ� �ڵ�
		return;
	}

	const wstring& itemName = unequipItemInstance.Get()->GetItemName();

	if (inventory.AddItem(move(unequipItemInstance)) == false)
	{
		m_textPrompt.Enqueue({ L"[����] : �κ��丮���� ������ �߰��� �����߽��ϴ�." });
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + itemName + L"] ��(��) �����߽��ϴ�.");
	EnableInventoryMenu();
	m_currentSceneState = EInventorySceneState::Default;
	return;
}
