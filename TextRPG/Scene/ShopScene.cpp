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

				const uint8 index = std::stoi(cmd) - 1;
				if (index >= 0 && index < static_cast<uint8>(m_shopItemList.size()))
				{
					HandleBuyCommand(index);
				}
				else
				{
					m_textPrompt.Enqueue(L"시스템 : 잘못된 입력입니다.");
					m_currentSceneState = EShopSceneState::Default;
					EnableShopMenu();
					return;
				}

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
	const vector<ItemInstance>& items = player.GetInventory().GetItemList();

	if (items.empty())
	{
		m_textPrompt.Enqueue(L"시스템 : 판매 가능 아이템이 없습니다.");
		m_currentSceneState = EShopSceneState::Default;
		EnableShopMenu();
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : 판매 가능 아이템:");

	for (size_t i = 0; i < items.size(); ++i)
	{
		const Item* item = items[i].Get(); 
		if (item == nullptr)
		{
			m_textPrompt.Enqueue(L"[오류] '" + std::to_wstring(i) + L"' 슬롯의 아이템을 찾을 수 없습니다.");
			continue;
		}

		const uint8 price = item->GetSellPrice();
		m_textPrompt.Enqueue(std::to_wstring(i + 1) + L". " + item->GetItemName() + L" - " + std::to_wstring(price) + L"G");
	}

	m_textPrompt.Enqueue(L"시스템 : '취소' 또는 아이템의 '번호'를 입력해 주세요.");
}

void ShopScene::HandleBuyCommand(const uint8 shopItemIndex)
{
	if (shopItemIndex >= m_shopItemList.size())
	{
		m_textPrompt.Enqueue({ L"[시스템] : 잘못된 번호를 입력했습니다." });
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
		m_textPrompt.Enqueue(L"시스템 : 인벤토리에 공간이 부족합니다.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().amount < item->GetBuyPrice() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 골드가 부족합니다.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetGold().RemoveGold(item->GetBuyPrice()) == false)
	{
		m_textPrompt.Enqueue(L"시스템 : 골드가 부족합니다.");
		EnableShopMenu();
		m_currentSceneState = EShopSceneState::Default;
		return;
	}

	if (player.GetInventory().AddItem(*item) == false)
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리에 아이템 저장 실패.");
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + item->GetItemName() + L"] 구매가 완료되었습니다.");
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
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 인덱스 범위를 초과했습니다.");
		return;
	}
	
	const Item* item = itemList[index].Get();
	wstring itemName = item->GetItemName();
	uint8 sellPrice = item->GetSellPrice();

	if (item == nullptr)
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 보유 아이템 검색에 실패했습니다.");
		return;
	}

	player.GetGold().AddGold(sellPrice);

	if (player.GetInventory().RemoveItem(itemName) == false)
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 보유 아이템 삭제에 실패했습니다.");
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + itemName + L"] 판매하였습니다. (+" + to_wstring(sellPrice) + L"G)");
	m_currentSceneState = EShopSceneState::Default;
	EnableShopMenu();
	return;
}
