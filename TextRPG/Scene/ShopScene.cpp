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

				const int index = std::stoi(cmd) - 1;
				if (index < 0 || index >= m_shopItemList.size())
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				HandleBuyCommand(index);
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

				PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
				const vector<Item*>& items = player.GetInventory().GetItemList();

				const int index = stoi(cmd) - 1;
				if (index < 0 || index >= items.size())
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				HandleSellCommand(index);
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
	m_screen.Write(73, 1, L"<< ���� >>");

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
	m_screen.Write(2, 14, L"����: " + (player.GetEquipment().GetWeapon() == nullptr ? L"������" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"��: " + (player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"�κ��丮 ");
	for (int i = 0; i < player.GetInventory().GetItemList().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItemList()[i]->GetItemName());
	}


	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer()); m_screen.Write(126, 30, L"��");
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
	const vector<Item*>& items = player.GetInventory().GetItemList();

	if (items.empty() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� �������� �����ϴ�.");
		m_currentSceneState = EShopSceneState::Default;
		EnableShopMenu();
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� ������:");

	for (size_t i = 0; i < items.size(); ++i)
	{
		const Item* item = GameInstance::GetInstance().GetItemTable().GetItem(items[i]->GetItemName());
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[����] '" + items[i]->GetItemName() + L"' �������� ã�� �� �����ϴ�.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"�ý��� : '���' �Ǵ� �������� '��ȣ'�� �Է��� �ּ���.");
}

void ShopScene::HandleBuyCommand(const uint8 shopItemIndex)
{
	if (m_shopItemList.size() < shopItemIndex)
	{
		m_textPrompt.Enqueue({ L"[�ý���] : �߸��� ��ȣ�� �Է��߽��ϴ�." });
		EnableBuyMenu();
		return;
	}

	const wstring& newItemName = m_shopItemList[shopItemIndex];
	const ItemTable& itemTable = GameInstance::GetInstance().GetItemTable();
	if (itemTable.HasItem(newItemName) == false)
	{
		m_textPrompt.Enqueue(L"[����] '" + m_shopItemList[shopItemIndex] + L"' �������� ã�� �� �����ϴ�.");
		return;
	}

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	Inventory& inventory = player.GetInventory();
	if (inventory.IsFull() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ������ �����մϴ�.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	const uint8 buyPrice = itemTable.GetItem(newItemName)->GetBuyPrice();
	if (player.GetGold().amount < buyPrice)
	{
		m_textPrompt.Enqueue(L"�ý��� : ��尡 �����մϴ�.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().RemoveGold(buyPrice) == false)
	{
		m_textPrompt.Enqueue(L"[����] : ���� ��� ������ ������ �߻��߽��ϴ�.");
		return;
	}

	const Item* buyItemInstace = itemTable.CreateItem(newItemName);
	if (inventory.AddItem(buyItemInstace) == false)
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮�� ������ �����ϴµ� ������ �߻��߽��ϴ�.");
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + buyItemInstace->GetItemName() + L"] ���Ű� �Ϸ�Ǿ����ϴ�.");
	EnableShopMenu();
	m_currentSceneState = EShopSceneState::Default;
	return;


	//const Item* item = GameInstance::GetInstance().GetItemTable().GetItem(m_shopItemList[shopItemIndex]);
	//if(buyItem == nullptr)
	//{
	//	m_textPrompt.Enqueue(L"[����] '" + m_shopItemList[shopItemIndex] + L"' �������� ã�� �� �����ϴ�.");
	//	return;
	//}

	//PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	//const uint8 price = buyItem->GetBuyPrice();

	//if (player.GetInventory().IsFull() == true)
	//{
	//	m_textPrompt.Enqueue(L"�ý��� : �κ��丮 ������ �����մϴ�.");
	//	EnableShopMenu();
	//	m_currentSceneState = EShopSceneState::Default;
	//	return;
	//}
	//
	//if (player.GetGold().amount < price)
	//{
	//	m_textPrompt.Enqueue(L"�ý��� : ��尡 �����մϴ�.");
	//	return;
	//}

	//Item* itemInstance = GameInstance::GetInstance().GetItemTable().CreateItem(buyItem->GetItemName());
	//const bool addItemResult = player.GetInventory().AddItem(itemInstance);
	//if(addItemResult == false)
	//{
	//	m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ���� �� �������� �������� ���߽��ϴ�.");
	//	EnableShopMenu();
	//	m_currentSceneState = EShopSceneState::Default;
	//}

	//player.GetGold().RemoveGold(price);
	//m_textPrompt.Enqueue(L"�ý��� : [" + itemInstance->GetItemName() + L"] ���Ű� �Ϸ�Ǿ����ϴ�.");
	//
	//EnableShopMenu();
	//m_currentSceneState = EShopSceneState::Default;
}

void ShopScene::HandleSellCommand(const wstring& cmd)
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	const vector<Item*>& items = player.GetInventory().GetItemList();

	const int index = std::stoi(cmd) - 1;
	const Item* item = items[index];
	if (item == nullptr)
	{
		m_textPrompt.Enqueue(L"[����] '" + items[index]->GetItemName() + L"' �������� ã�� �� �����ϴ�.");
		return;
	}

	const uint8 price = item->GetSellPrice();
	player.GetGold().AddGold(price);
	player.GetInventory().RemoveItem(item->GetItemName());
	m_textPrompt.Enqueue(L"�ý��� : [" + item->GetItemName() + L"] �Ǹ��Ͽ����ϴ�. (+" + std::to_wstring(price) + L"G)");

	EnableShopMenu();
	m_currentSceneState = EShopSceneState::Default;
}

void ShopScene::HandleSellCommand(const uint8 inventoryItemIndex)
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	Inventory& inventory = player.GetInventory();

	const Item* sellItem = inventory.GetItemList()[inventoryItemIndex];
	if (sellItem == nullptr)
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 ���� ������ �˻��� �����߽��ϴ�.");
		return;
	}

	const uint8 sellPrice = sellItem->GetSellPrice();
	player.GetGold().AddGold(sellPrice);

	if (player.GetInventory().RemoveItem(sellItem->GetItemName()))
	{
		m_textPrompt.Enqueue(L"[����] : �κ��丮 ���� ������ ������ �����߽��ϴ�.");
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : [" + sellItem->GetItemName() + L"] �Ǹ��Ͽ����ϴ�. (+" + std::to_wstring(sellPrice) + L"G)");

	EnableShopMenu();
	m_currentSceneState = EShopSceneState::Default;
	return;
}
