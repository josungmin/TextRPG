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

	m_textPrompt.Enqueue(L"시스템 : 인벤토리를 엽니다.");
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
				if (cmd == L"1" || cmd == L"장착" || cmd == L"아이템장착" || cmd == L"1.아이템장착")
				{
					m_currentSceneState = EInventorySceneState::Equip;
					EnableEquipMenu();
				}
				else if (cmd == L"2" || cmd == L"해제" || cmd == L"아이템해제" || cmd == L"1.아이템해제")
				{
					m_currentSceneState = EInventorySceneState::Unequip;
					EnableUnequipMenu();
				}
				else if (cmd == L"3" || cmd == L"나가기")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"시스템 : 인식할 수 없는 명령입니다. 다시 입력해 주세요.");
				}
				break;
			}
			case InventoryScene::EInventorySceneState::Equip:
			{
				if (cmd == L"취소")
				{
					EnableInventoryMenu();
					m_currentSceneState = EInventorySceneState::Default;
					return;
				}

				const int index = std::stoi(cmd);
				if (index < 0 || GameInstance::GetInstance().GetPlayer().GetInventory().GetItemList().size() < index)
				{
					m_textPrompt.Enqueue(L"시스템 : 잘못된 입력입니다.");
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

void InventoryScene::EnableInventoryMenu()
{
	m_textPrompt.Enqueue(L"시스템 : 어떤 행동을 하시겠습니까?");
	m_textPrompt.Enqueue(L"시스템 : 1.아이템 장착 2.아이템 해제 3.나가기");
}

void InventoryScene::EnableEquipMenu()
{	
	const vector<ItemInstance>& itemList = GameInstance::GetInstance().GetPlayer().GetInventory().GetItemList();

	if (itemList.empty() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 장착할 아이템이 존재하지 않습니다.");
		EnableInventoryMenu();
		m_currentSceneState = EInventorySceneState::Default;
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : 어떤 아이템을 [장착] 하시겠습니까? 번호를 입력해주세요.");

	for (uint8 i = 0; i < itemList.size(); ++i)
	{
		m_textPrompt.Enqueue(L"인벤토리 : [" + to_wstring(i) + L"] " + itemList[i].Get()->GetItemName());
	}
}

void InventoryScene::EnableUnequipMenu()
{
	Equipment& equipment = GameInstance::GetInstance().GetPlayer().GetEquipment();
	const EquipableItem* weapon = equipment.GetEquipedItem(EquipableItem::EEquipType::Weapon);
	const EquipableItem* armor = equipment.GetEquipedItem(EquipableItem::EEquipType::Armor);

	m_textPrompt.Enqueue(L"시스템 : 어떤 아이템을 [해제] 하시겠습니까? 번호를 입력해주세요.");
	m_textPrompt.Enqueue(L"인벤토리 : [0] " + (weapon == nullptr ? L"비어있음" : weapon->GetItemName()));
	m_textPrompt.Enqueue(L"인벤토리 : [1] " + (armor == nullptr ? L"비어있음" : armor->GetItemName()));
}

void InventoryScene::HandleEquipCommand(const uint8 equipItemIndex)
{
	Inventory& inventory = GameInstance::GetInstance().GetPlayer().GetInventory();
	if (equipItemIndex < 0 || equipItemIndex >= static_cast<uint8>(inventory.GetItemList().size()))
	{
		m_textPrompt.Enqueue(L"[오류] : 인덱스 범위를 초과했습니다. 다시 입력해주세요.");
		return;
	}

	const EquipableItem* selectedItem = inventory.GetItemList()[equipItemIndex].Get<EquipableItem>();
	if (selectedItem == nullptr)
	{
		m_textPrompt.Enqueue({ L"[오류] : 아이템이 존재하지 않습니다." });
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
			m_textPrompt.Enqueue({ L"[오류] : 인벤토리에서 아이템 추가에 실패했습니다." });
			m_textPrompt.Enqueue({ L"[오류] : unequipItemInstance is not valid" }); // TODO : 임시 코드
			return;
		}
		
		if (inventory.AddItem(move(unequipItemInstance)) == false)
		{
			m_textPrompt.Enqueue({ L"[오류] : 인벤토리에서 아이템 추가에 실패했습니다." });
			return;
		}
	}

	const wstring& itemName = selectedItem->GetItemName();
	ItemInstance equipItemInstance = inventory.RemoveItem(itemName);
	if (equipItemInstance.IsValid() == false)
	{
		m_textPrompt.Enqueue({ L"[오류] : 인벤토리에서 아이템 추가에 실패했습니다." });
		m_textPrompt.Enqueue({ L"[오류] : equipItemInstance is not valid" }); // TODO : 임시 코드
		return;
	}

	if (equipment.EquipItem(move(equipItemInstance), statContainer) == false)
	{
		m_textPrompt.Enqueue({ L"[오류] : 아이템 장착에 실패했습니다." });
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + itemName + L"] 을(를) 장착했습니다.");
	EnableInventoryMenu();
	m_currentSceneState = EInventorySceneState::Default;
}

// TODO: 수정 필요 - 아이템 해제의 인덱스 범위 초과 출력됨
void InventoryScene::HandleUnequipCommand(const wstring& cmd)
{
	Inventory& inventory = GameInstance::GetInstance().GetPlayer().GetInventory();
	Equipment& equipment = GameInstance::GetInstance().GetPlayer().GetEquipment();
	StatContainer& statContainer = GameInstance::GetInstance().GetPlayer().GetStats();

	if (inventory.IsFull())
	{
		m_textPrompt.Enqueue({ L"[시스템] : 인벤토리 공간이 부족합니다." });
		EnableInventoryMenu();
		m_currentSceneState = EInventorySceneState::Default;
	}

	const uint8 index = static_cast<uint8>(stoi(cmd)) - 1;
	if (index <= 0 || index >= static_cast<uint8>(EquipableItem::EEquipType::Max))
	{
		m_textPrompt.Enqueue(L"[오류] : 인벤토리 인덱스 범위를 초과했습니다. 다시 입력해주세요.");
		return;
	}

	const EquipableItem::EEquipType selectedEquipType = static_cast<EquipableItem::EEquipType>(index);

	ItemInstance unequipItemInstance = equipment.UnequipItem(selectedEquipType, statContainer);
	if (unequipItemInstance.IsValid() == false)
	{
		m_textPrompt.Enqueue({ L"[오류] : 인벤토리에서 아이템 추가에 실패했습니다." });
		m_textPrompt.Enqueue({ L"[오류] : unequipItemInstance is not valid" }); // TODO : 임시 코드
		return;
	}

	const wstring& itemName = unequipItemInstance.Get()->GetItemName();

	if (inventory.AddItem(move(unequipItemInstance)) == false)
	{
		m_textPrompt.Enqueue({ L"[오류] : 인벤토리에서 아이템 추가에 실패했습니다." });
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : [" + itemName + L"] 을(를) 해제했습니다.");
	EnableInventoryMenu();
	m_currentSceneState = EInventorySceneState::Default;
	return;
}
