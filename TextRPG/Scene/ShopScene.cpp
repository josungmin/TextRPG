#include "ShopScene.h"
#include "../GameInstance.h"
#include "MainScene.h"

ShopScene::ShopScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
{
	m_shopItemList.reserve(4);
	m_shopItemList.push_back(L"���ϱ� ��");
	m_shopItemList.push_back(L"�ϱ� ��");
	m_shopItemList.push_back(L"�Ϲ� ��");
	m_shopItemList.push_back(L"���ϱ� ����");

	m_currentSceneState = EShopSceneState::Default;
}

void ShopScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	EnableShopMenu();
}

void ShopScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void ShopScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand() == true)
	{
		std::wstring cmd = m_input.GetCommand();

		switch (m_currentSceneState)
		{
			case EShopSceneState::Default:
			{
				if (cmd == L"1" || cmd == L"����")
				{	
					m_currentSceneState = EShopSceneState::Buy;
					EnableBuyMenu();			
				}
				else if (cmd == L"2" || cmd == L"�Ǹ�")
				{
					m_currentSceneState = EShopSceneState::Sell;
					EnableSellMenu();		
				}
				else if (cmd == L"3" || cmd == L"������")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
				}
				break;
			}			
			case EShopSceneState::Buy:
			{
				if (cmd == L"���")
				{
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				const uint8 index = std::stoi(cmd) - 1;
				if (index >= 0 && index < static_cast<uint8>(m_shopItemList.size()))
				{
					HandleBuyCommand(index);
				}
				else
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				break;
			}
			case EShopSceneState::Sell:
			{
				if (cmd == L"���")
				{
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();	
					return;
				}

				HandleSellCommand(cmd);
				break;
			}
			default:
			{
				break;
			}
		}

	}
}

void ShopScene::Render()
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

void ShopScene::EnableShopMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
	m_textPrompt.Enqueue(L"1.����  2.�Ǹ�  3.������");
}

void ShopScene::EnableBuyMenu()
{
	ItemTable& itemTable = GameInstance::GetInstance().GetItemTable();

	m_textPrompt.Enqueue(L"�ý��� : ���� ���� ������:");

	for (int32 i = 0; i < m_shopItemList.size(); ++i)
	{
		const Item* item = itemTable.GetItem(m_shopItemList[i]);
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[����] '" + m_shopItemList[i] + L"' �������� ã�� �� �����ϴ�.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"�ý��� : '���' �Ǵ� �������� '��ȣ'�� �Է��� �ּ���.");
}

void ShopScene::EnableSellMenu()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	const vector<ItemInstance>& items = player.GetInventory().GetItemList();

	if (items.empty())
	{
		m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� �������� �����ϴ�.");
		m_currentSceneState = EShopSceneState::Default;
		EnableShopMenu();
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� ������:");

	for (size_t i = 0; i < items.size(); ++i)
	{
		const Item* item = items[i].Get(); 
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[����] '" + std::to_wstring(i) + L"' ������ �������� ã�� �� �����ϴ�.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"�ý��� : '���' �Ǵ� �������� '��ȣ'�� �Է��� �ּ���.");
}

void ShopScene::HandleBuyCommand(const uint8 shopItemIndex)
{
	if (shopItemIndex >= m_shopItemList.size())
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �߸��� ��ȣ�� �Է��߽��ϴ�." });
		EnableBuyMenu();
		return;
	}

	const Item* item = GameInstance::GetInstance().GetItemTable().GetItem(m_shopItemList[shopItemIndex]);
	if (item == nullptr)
	{
		return;
	}

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	if (player.GetInventory().IsFull() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ������ �����մϴ�.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().amount < item->GetBuyPrice() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : ��尡 �����մϴ�.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().RemoveGold(item->GetBuyPrice()) == false)
	{
		m_textPrompt.Enqueue(L"�ý��� : ��尡 �����մϴ�.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetInventory().AddItem(*item) == false)
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮�� ������ ���� ����.");
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + item->GetItemName() + L"] ���Ű� �Ϸ�Ǿ����ϴ�.");
	m_currentSceneState = EShopSceneState::Default;
	EnableShopMenu();
}

void ShopScene::HandleSellCommand(const std::wstring& cmd)
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

	const uint8 index = std::stoi(cmd) - 1;
	const vector<ItemInstance>& itemList = player.GetInventory().GetItemList();
	if (index < 0 || index >= static_cast<int>(itemList.size()))
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 �ε��� ������ �ʰ��߽��ϴ�.");
		return;
	}
	
	const Item* item = itemList[index].Get();
	wstring itemName = item->GetItemName();
	uint8 sellPrice = item->GetSellPrice();

	if (item == nullptr)
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 ���� ������ �˻��� �����߽��ϴ�.");
		return;
	}

	player.GetGold().AddGold(sellPrice);

	if (player.GetInventory().RemoveItem(itemName) == false)
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 ���� ������ ������ �����߽��ϴ�.");
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + itemName + L"] �Ǹ��Ͽ����ϴ�. (+" + to_wstring(sellPrice) + L"G)");
	m_currentSceneState = EShopSceneState::Default;
	EnableShopMenu();
	return;
}
