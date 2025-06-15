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

ShopScene::~ShopScene()
{
	
}

void ShopScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	ShowShopMenu();
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
					ShowBuyMenu();			
				}
				else if (cmd == L"2" || cmd == L"�Ǹ�")
				{
					m_currentSceneState = EShopSceneState::Sell;
					ShowSellMenu();		
				}
				else if (cmd == L"3" || cmd == L"������")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
				}
				break;
			}			
			case EShopSceneState::Buy:
			{
				if (cmd == L"���")
				{
					m_currentSceneState = EShopSceneState::Default;
					ShowShopMenu();
					return;
				}

				const int index = std::stoi(cmd) - 1;
				if (index < 0 || index >= m_shopItemList.size())
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					m_currentSceneState = EShopSceneState::Default;
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
					ShowShopMenu();	
					return;
				}

				PlayerCharacter& player = GameInstance::Instance().GetPlayer();
				const vector<Item*>& items = player.GetInventory().GetItemList();

				const int index = stoi(cmd) - 1;
				if (index < 0 || index >= items.size())
				{
					m_textPrompt.Enqueue(L"�ý��� : �߸��� �Է��Դϴ�.");
					m_currentSceneState = EShopSceneState::Default;
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
	m_screen.Write(73, 1, L"<< ���� >>");

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
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer()); m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}

void ShopScene::ShowShopMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
	m_textPrompt.Enqueue(L"1.����  2.�Ǹ�  3.������");
}

void ShopScene::ShowBuyMenu()
{
	m_textPrompt.Enqueue(L"�ý��� : ���� ���� ������:");

	for (int32 i = 0; i < m_shopItemList.size(); ++i)
	{
		const Item* item = GameInstance::Instance().GetItemTable().GetItem(m_shopItemList[i]);
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

void ShopScene::ShowSellMenu()
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	const vector<Item*>& items = player.GetInventory().GetItemList();

	if (items.empty() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� �������� �����ϴ�.");
		m_currentSceneState = EShopSceneState::Default;
		ShowShopMenu();
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : �Ǹ� ���� ������:");

	for (size_t i = 0; i < items.size(); ++i)
	{
		const Item* item = GameInstance::Instance().GetItemTable().GetItem(items[i]->GetItemName());
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[����] '" + items[i]->GetItemName() + L"' �������� ã�� �� �����ϴ�.");
			continue;
		}

		const uint8 price = item->GetBuyPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"�ý��� : '���' �Ǵ� �������� '��ȣ'�� �Է��� �ּ���.");
}

void ShopScene::HandleBuyCommand(const uint8 shopItemIndex)
{
	const Item* item = GameInstance::Instance().GetItemTable().GetItem(m_shopItemList[shopItemIndex]);
	if(item == nullptr)
	{
		m_textPrompt.Enqueue(L"[����] '" + m_shopItemList[shopItemIndex] + L"' �������� ã�� �� �����ϴ�.");
		return;
	}

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	const uint8 price = item->GetBuyPrice();
	
	if (player.GetGold().m_amount < price)
	{
		m_textPrompt.Enqueue(L"�ý��� : ��尡 �����մϴ�.");
		return;
	}

	Item* itemInstance = GameInstance::Instance().GetItemTable().CreateItem(item->GetItemName());
	const bool addItemResult = player.GetInventory().AddItem(itemInstance);
	if(addItemResult == false)
	{
		m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ���� �� �������� �������� ���߽��ϴ�.");
		ShowShopMenu();
		m_currentSceneState = EShopSceneState::Default;
	}

	player.GetGold().AddGold(price);
	m_textPrompt.Enqueue(L"�ý��� : [" + itemInstance->GetItemName() + L"] ���Ű� �Ϸ�Ǿ����ϴ�.");
	
	ShowShopMenu();
	m_currentSceneState = EShopSceneState::Default;
}

void ShopScene::HandleSellCommand(const wstring& cmd)
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
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

	ShowShopMenu();
	m_currentSceneState = EShopSceneState::Default;
}