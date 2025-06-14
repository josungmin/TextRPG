#include "MainScene.h"
#include <string>
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "../Item/Item.h"
#include "../Item/EquipableItem.h"
#include "ShopScene.h"
#include "DungeonScene.h"



MainScene::MainScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt)
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

	m_textPrompt.Enqueue(L"衛蝶蠱 : 葆擊縑 殮濰м棲棻.");
	ShowMainMenu();
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
		PlayerCharacter& player = GameInstance::Instance().GetPlayer();

		switch (m_currentSceneState)
		{
		case EMainSceneState::Default:
		{
			if (cmd == L"1" || cmd == L"��楝" || cmd == L"1.��楝")
			{
				m_textPrompt.Enqueue(L"衛蝶蠱 : ��楝縑啪 棻陛陛 蜓擊 匏棲棻.");
				m_textPrompt.Enqueue(L"��楝 : 500埤萄蒂 輿賊 傘曖 羹溘擊 賅舒 �蛹厭藥� 還啪!");
				m_textPrompt.Enqueue(L"衛蝶蠱 : 1.熱塊 2.剪瞰");
				m_currentSceneState = EMainSceneState::Healer;
			}
			else if (cmd == L"2" || cmd == L"鼻薄" || cmd == L"2.鼻薄")
			{
				Scene* shopScene = new ShopScene(m_screen, m_input, m_textPrompt);
				GameInstance::Instance().GetSceneManager().ChangeScene(*shopScene);
			}
			else if (cmd == L"3" || cmd == L"檣漸饜葬" || cmd == L"3.檣漸饜葬")
			{
				m_textPrompt.Enqueue(L"衛蝶蠱 : '[嬴檜蠱貲] 濰雜', '[嬴檜蠱貲] п薯' �分� '釭陛晦'蒂 殮溘ж撮蹂.");
				m_currentSceneState = EMainSceneState::Inventory;
			}
			else if (cmd == L"4" || cmd == L"湍瞪" || cmd == L"4.湍瞪")
			{
				Scene* dungeonScene = new DungeonScene(m_screen, m_input, m_textPrompt);
				GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
			}
			else
			{
				m_textPrompt.Enqueue(L"衛蝶蠱 : 檣衝й 熱 橈朝 貲滄殮棲棻. 棻衛 殮溘п 輿撮蹂.");
			}
			break;
		}
		case EMainSceneState::Healer:
		{
			if (cmd == L"1" || cmd == L"熱塊" || cmd == L"1.熱塊")
			{
				HandleHealCommand();
			}
			else if (cmd == L"2" || cmd == L"剪瞰" || cmd == L"2.剪瞰")
			{
				m_textPrompt.Enqueue(L"��楝 : 棻擠縑 傳諦.");
				m_currentSceneState = EMainSceneState::Default;
				ShowMainMenu();
			}
			else
			{
				m_textPrompt.Enqueue(L"衛蝶蠱 : 檣衝й 熱 橈朝 貲滄殮棲棻. 棻衛 殮溘п 輿撮蹂.");
			}
			break;
		}
		case EMainSceneState::Inventory:
		{
			if (cmd == L"釭陛晦")
			{
				ShowMainMenu();
				m_currentSceneState = EMainSceneState::Default;
				return;
			}

			for (Item* item : player.GetInventory().GetItemList())
			{
				if (cmd == item->GetItemName() + L"濰雜")
				{
					if (const EquipableItem* equipItem = dynamic_cast<EquipableItem*>(item))
					{
						HandleEquipCommand(equipItem);
						return;
					}
				}
			}

			if (const EquipableItem* weapon = player.GetEquipment().GetWeapon())
			{
				if (cmd == weapon->GetItemName() + L"п薯")
				{
					HandleUnequipCommand(weapon->GetEquipType());
					return;
				}
			}

			if (const EquipableItem* armor = player.GetEquipment().GetArmor())
			{
				if (cmd == armor->GetItemName() + L"п薯")
				{
					HandleUnequipCommand(armor->GetEquipType());
					return;
				}
			}

			m_textPrompt.Enqueue(L"衛蝶蠱 : 檣衝й 熱 橈朝 貲滄殮棲棻. 棻衛 殮溘п 輿撮蹂.");
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
	m_screen.Write(0, 0, L"忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"弛");
		m_screen.Write(32, y, L"弛");
		m_screen.Write(126, y, L"弛");
	}

	m_screen.Write(13, 1, L"[ 棟溘纂 ]");
	m_screen.Write(73, 1, L"<< 葆擊 >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	m_screen.Write(2, 3, L"檜葷: " + player.GetName());
	m_screen.Write(2, 4, L"薑爾: " + player.GetDescription());
	m_screen.Write(2, 5, L"溯漣: " + to_wstring(player.GetExperience().m_level));
	m_screen.Write(2, 6, L"唳я纂: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().m_currentExp));
	m_screen.Write(2, 7, L"埤萄: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"奢問溘: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"寞橫溘: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"團繪: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"濰雜 嬴檜蠱");
	m_screen.Write(2, 14, L"鼠晦: " + (player.GetEquipment().GetWeapon() == nullptr ? L"嘐濰雜" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"寞橫掘: " + (player.GetEquipment().GetArmor() == nullptr ? L"嘐濰雜" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"檣漸饜葬 ");
	for (int i = 0; i < player.GetInventory().GetItemList().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItemList()[i]->GetItemName());
	}
	m_screen.Write(0, 29, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	m_screen.Write(0, 30, L"弛"); m_screen.Write(2, 30, L"貲滄 > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"弛");
	m_screen.Write(0, 31, L"戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
}

void MainScene::ShowMainMenu()
{
	m_textPrompt.Enqueue(L"衛蝶蠱 : 橫雯 ч翕擊 ж衛啊蝗棲梱?");
	m_textPrompt.Enqueue(L"衛蝶蠱 : 1.�蛹� 2.鼻薄 3.檣漸饜葬 4.湍瞪");
}

void MainScene::HandleHealCommand()
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	const uint16 playerMaxHP = player.GetStats().GetStatValue(EStatType::HP);

	if (player.GetCurrentHP() == playerMaxHP)
	{
		m_textPrompt.Enqueue({ L"��楝 : 傘 檜嘐 羹溘檜 棻 �蛹僱�匙 偽嬴..." });
	}
	else if (player.GetGold().RemoveGold(500))
	{
		player.HealHp(playerMaxHP);
		m_textPrompt.Enqueue({ L"��楝 : 傘曖 羹溘擊 賅舒 �蛹厭藥袛�!" });
	}
	else
	{
		m_textPrompt.Enqueue({ L"��楝 : 絲檜 氈橫撿 �蛹嘛� 衛麵還 熱 氈橫!" });
	}

	m_currentSceneState = EMainSceneState::Default;
	ShowMainMenu();
}

void MainScene::HandleEquipCommand(const EquipableItem* equipItem)
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();
	Inventory& inventory = player.GetInventory();
	StatContainer& stats = player.GetStats();
	const EEquipType equipType = equipItem->GetEquipType();

	if (equipment.IsEquiped(equipType) == true)
	{
		if (inventory.IsFull() == true)
		{
			m_textPrompt.Enqueue({ L"衛蝶蠱 : 檣漸饜葬縑 奢除檜 睡褶м棲棻." });
			m_textPrompt.Enqueue(L"衛蝶蠱 : '嬴檜蠱貲 濰雜' 傳朝 '嬴檜蠱貲 п薯'蒂 殮溘ж剪釭, '釭陛晦'蒂 殮溘ж撮蹂.");
			return;
		}

		const EquipableItem* unequipItem = equipment.Unequip(equipType, stats);
		if (unequipItem == nullptr)
		{
			m_textPrompt.Enqueue({ L"[螃盟] : 晦襄 嬴檜蠱擊 п薯ж朝等 僥薯陛 嫦儅ц蝗棲棻." });
			return;
		}

		if (inventory.AddItem(unequipItem) == false)
		{
			m_textPrompt.Enqueue({ L"[螃盟] : 晦襄 嬴檜蠱擊 п薯ж朝等 僥薯陛 嫦儅ц蝗棲棻." });
			return;
		}
	}

	if (equipment.Equip(equipItem, stats) == false)
	{
		m_textPrompt.Enqueue({ L"[螃盟] : 億煎遴 嬴檜蠱擊 濰雜ж朝等 僥薯陛 嫦儅ц蝗棲棻." });
		return;
	}

	m_textPrompt.Enqueue(L"衛蝶蠱 : [" + equipItem->GetItemName() + L"] 擊(蒂) 濰雜ц蝗棲棻.");
	m_textPrompt.Enqueue(L"衛蝶蠱 : '嬴檜蠱貲 濰雜' 傳朝 '嬴檜蠱貲 п薯'蒂 殮溘ж剪釭, '釭陛晦'蒂 殮溘ж撮蹂.");
	return;
}

void MainScene::HandleUnequipCommand(const EEquipType equipType)
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();
	Inventory& inventory = player.GetInventory();
	StatContainer& stats = player.GetStats();

	if (inventory.IsFull() == true)
	{
		m_textPrompt.Enqueue({ L"衛蝶蠱 : 檣漸饜葬縑 奢除檜 睡褶м棲棻." });
		m_textPrompt.Enqueue(L"衛蝶蠱 : '嬴檜蠱貲 濰雜' 傳朝 '嬴檜蠱貲 п薯'蒂 殮溘ж剪釭, '釭陛晦'蒂 殮溘ж撮蹂.");
		return;
	}

	const EquipableItem* unequipped = equipment.Unequip(equipType, stats);
	if (unequipped != nullptr || inventory.AddItem(unequipped) == true)
	{
		m_textPrompt.Enqueue(L"[螃盟] : 晦襄 嬴檜蠱擊 п薯ж朝等 僥薯陛 嫦儅ц蝗棲棻.");
		return;
	}

	m_textPrompt.Enqueue(L"衛蝶蠱 : [" + unequipped->GetItemName() + L"] 擊(蒂) п薯ц蝗棲棻.");
	m_textPrompt.Enqueue(L"衛蝶蠱 : '嬴檜蠱貲 濰雜' 傳朝 '嬴檜蠱貲 п薯'蒂 殮溘ж剪釭, '釭陛晦'蒂 殮溘ж撮蹂.");
	return;
}
