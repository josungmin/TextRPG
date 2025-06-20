#include "ShopScene.h"
#include "../GameInstance.h"
#include "MainScene.h"

ShopScene::ShopScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
{
	m_shopItemList.reserve(4);
	m_shopItemList.push_back(L"최하급 검");
	m_shopItemList.push_back(L"하급 검");
	m_shopItemList.push_back(L"일반 검");
	m_shopItemList.push_back(L"최하급 갑옷");

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
				if (cmd == L"1" || cmd == L"구매")
				{	
					m_currentSceneState = EShopSceneState::Buy;
					EnableBuyMenu();			
				}
				else if (cmd == L"2" || cmd == L"판매")
				{
					m_currentSceneState = EShopSceneState::Sell;
					EnableSellMenu();		
				}
				else if (cmd == L"3" || cmd == L"나가기")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
				}
				break;
			}			
			case EShopSceneState::Buy:
			{
				if (cmd == L"취소")
				{
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				const int index = std::stoi(cmd) - 1;
				if (index < 0 || index >= m_shopItemList.size())
				{
					m_textPrompt.Enqueue(L"시스템 : 잘못된 입력입니다.");
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

				HandleBuyCommand(index);
				break;
			}
			case EShopSceneState::Sell:
			{
				if (cmd == L"취소")
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
					m_textPrompt.Enqueue(L"시스템 : 잘못된 입력입니다.");
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
	m_screen.Write(0, 0, L"┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"│");
		m_screen.Write(32, y, L"│");
		m_screen.Write(126, y, L"│");
	}

	m_screen.Write(13, 1, L"[ 능력치 ]");
	m_screen.Write(73, 1, L"<< 상점 >>");

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
	m_screen.Write(2, 14, L"무기: " + (player.GetEquipment().GetWeapon() == nullptr ? L"미장착" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"방어구: " + (player.GetEquipment().GetArmor() == nullptr ? L"미장착" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"인벤토리 ");
	for (int i = 0; i < player.GetInventory().GetItemList().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItemList()[i]->GetItemName());
	}


	m_screen.Write(0, 29, L"│─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────│");
	m_screen.Write(0, 30, L"│"); m_screen.Write(2, 30, L"명령 > " + m_input.GetInputBuffer()); m_screen.Write(126, 30, L"│");
	m_screen.Write(0, 31, L"└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘");
}

void ShopScene::EnableShopMenu()
{
	m_textPrompt.Enqueue(L"시스템 : 상점에 입장합니다.");
	m_textPrompt.Enqueue(L"1.구매  2.판매  3.나가기");
}

void ShopScene::EnableBuyMenu()
{
	ItemTable& itemTable = GameInstance::GetInstance().GetItemTable();

	m_textPrompt.Enqueue(L"시스템 : 구매 가능 아이템:");

	for (int32 i = 0; i < m_shopItemList.size(); ++i)
	{
		const Item* item = itemTable.GetItem(m_shopItemList[i]);
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[오류] '" + m_shopItemList[i] + L"' 아이템을 찾을 수 없습니다.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"시스템 : '취소' 또는 아이템의 '번호'를 입력해 주세요.");
}

void ShopScene::EnableSellMenu()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	const vector<Item*>& items = player.GetInventory().GetItemList();

	if (items.empty() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 판매 가능 아이템이 없습니다.");
		m_currentSceneState = EShopSceneState::Default;
		EnableShopMenu();
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : 판매 가능 아이템:");

	for (size_t i = 0; i < items.size(); ++i)
	{
		const Item* item = GameInstance::GetInstance().GetItemTable().GetItem(items[i]->GetItemName());
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[오류] '" + items[i]->GetItemName() + L"' 아이템을 찾을 수 없습니다.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"시스템 : '취소' 또는 아이템의 '번호'를 입력해 주세요.");
}

void ShopScene::HandleBuyCommand(const uint8 shopItemIndex)
{
	if (m_shopItemList.size() < shopItemIndex)
	{
		m_textPrompt.Enqueue({ L"[시스템] : 잘못된 번호를 입력했습니다." });
		EnableBuyMenu();
		return;
	}

	const wstring& newItemName = m_shopItemList[shopItemIndex];
	const ItemTable& itemTable = GameInstance::GetInstance().GetItemTable();
	if (itemTable.HasItem(newItemName) == false)
	{
		m_textPrompt.Enqueue(L"[오류] '" + m_shopItemList[shopItemIndex] + L"' 아이템을 찾을 수 없습니다.");
		return;
	}

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	Inventory& inventory = player.GetInventory();
	if (inventory.IsFull() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 인벤토리에 공간이 부족합니다.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	const uint8 buyPrice = itemTable.GetItem(newItemName)->GetBuyPrice();
	if (player.GetGold().amount < buyPrice)
	{
		m_textPrompt.Enqueue(L"시스템 : 골드가 부족합니다.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().RemoveGold(buyPrice) == false)
	{
		m_textPrompt.Enqueue(L"[오류] : 보유 골드 차감에 문제가 발생했습니다.");
		return;
	}

	const Item* buyItemInstace = itemTable.CreateItem(newItemName);
	if (inventory.AddItem(buyItemInstace) == false)
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리에 아이템 저장하는데 문제가 발생했습니다.");
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + buyItemInstace->GetItemName() + L"] 구매가 완료되었습니다.");
	EnableShopMenu();
	m_currentSceneState = EShopSceneState::Default;
	return;


	//const Item* item = GameInstance::GetInstance().GetItemTable().GetItem(m_shopItemList[shopItemIndex]);
	//if(buyItem == nullptr)
	//{
	//	m_textPrompt.Enqueue(L"[오류] '" + m_shopItemList[shopItemIndex] + L"' 아이템을 찾을 수 없습니다.");
	//	return;
	//}

	//PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	//const uint8 price = buyItem->GetBuyPrice();

	//if (player.GetInventory().IsFull() == true)
	//{
	//	m_textPrompt.Enqueue(L"시스템 : 인벤토리 공간이 부족합니다.");
	//	EnableShopMenu();
	//	m_currentSceneState = EShopSceneState::Default;
	//	return;
	//}
	//
	//if (player.GetGold().amount < price)
	//{
	//	m_textPrompt.Enqueue(L"시스템 : 골드가 부족합니다.");
	//	return;
	//}

	//Item* itemInstance = GameInstance::GetInstance().GetItemTable().CreateItem(buyItem->GetItemName());
	//const bool addItemResult = player.GetInventory().AddItem(itemInstance);
	//if(addItemResult == false)
	//{
	//	m_textPrompt.Enqueue(L"시스템 : 인벤토리가 가득 차 아이템을 구매하지 못했습니다.");
	//	EnableShopMenu();
	//	m_currentSceneState = EShopSceneState::Default;
	//}

	//player.GetGold().RemoveGold(price);
	//m_textPrompt.Enqueue(L"시스템 : [" + itemInstance->GetItemName() + L"] 구매가 완료되었습니다.");
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
		m_textPrompt.Enqueue(L"[오류] '" + items[index]->GetItemName() + L"' 아이템을 찾을 수 없습니다.");
		return;
	}

	const uint8 price = item->GetSellPrice();
	player.GetGold().AddGold(price);
	player.GetInventory().RemoveItem(item->GetItemName());
	m_textPrompt.Enqueue(L"시스템 : [" + item->GetItemName() + L"] 판매하였습니다. (+" + std::to_wstring(price) + L"G)");

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
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 보유 아이템 검색에 실패했습니다.");
		return;
	}

	const uint8 sellPrice = sellItem->GetSellPrice();
	player.GetGold().AddGold(sellPrice);

	if (player.GetInventory().RemoveItem(sellItem->GetItemName()))
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 보유 아이템 삭제에 실패했습니다.");
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + sellItem->GetItemName() + L"] 판매하였습니다. (+" + std::to_wstring(sellPrice) + L"G)");

	EnableShopMenu();
	m_currentSceneState = EShopSceneState::Default;
	return;
}
