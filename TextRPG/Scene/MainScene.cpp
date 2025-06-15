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

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¸¶À»¿¡ ÀÔÀåÇÕ´Ï´Ù.");
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
			if (cmd == L"1" || cmd == L"Èú·¯" || cmd == L"1.Èú·¯")
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : Èú·¯¿¡°Ô ´Ù°¡°¡ ¸»À» °Ì´Ï´Ù.");
				m_textPrompt.Enqueue(L"Èú·¯ : 500°ñµå¸¦ ÁÖ¸é ³ÊÀÇ Ã¼·ÂÀ» ¸ðµÎ È¸º¹½ÃÄÑ ÁÙ°Ô!");
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.¼ö¶ô 2.°ÅÀý");
				m_currentSceneState = EMainSceneState::Healer;
			}
			else if (cmd == L"2" || cmd == L"»óÁ¡" || cmd == L"2.»óÁ¡")
			{
				Scene* shopScene = new ShopScene(m_screen, m_input, m_textPrompt);
				GameInstance::Instance().GetSceneManager().ChangeScene(*shopScene);
			}
			else if (cmd == L"3" || cmd == L"ÀÎº¥Åä¸®" || cmd == L"3.ÀÎº¥Åä¸®")
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '[¾ÆÀÌÅÛ¸í] ÀåÂø', '[¾ÆÀÌÅÛ¸í] ÇØÁ¦' È¤Àº '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
				m_currentSceneState = EMainSceneState::Inventory;
			}
			else if (cmd == L"4" || cmd == L"´øÀü" || cmd == L"4.´øÀü")
			{
				Scene* dungeonScene = new DungeonScene(m_screen, m_input, m_textPrompt);
				GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
			}
			else
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎ½ÄÇÒ ¼ö ¾ø´Â ¸í·ÉÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØ ÁÖ¼¼¿ä.");
			}
			break;
		}
		case EMainSceneState::Healer:
		{
			if (cmd == L"1" || cmd == L"¼ö¶ô" || cmd == L"1.¼ö¶ô")
			{
				HandleHealCommand();
			}
			else if (cmd == L"2" || cmd == L"°ÅÀý" || cmd == L"2.°ÅÀý")
			{
				m_textPrompt.Enqueue(L"Èú·¯ : ´ÙÀ½¿¡ ¶Ç¿Í.");
				m_currentSceneState = EMainSceneState::Default;
				ShowMainMenu();
			}
			else
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎ½ÄÇÒ ¼ö ¾ø´Â ¸í·ÉÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØ ÁÖ¼¼¿ä.");
			}
			break;
		}
		case EMainSceneState::Inventory:
		{
			if (cmd == L"³ª°¡±â")
			{
				ShowMainMenu();
				m_currentSceneState = EMainSceneState::Default;
				return;
			}

			for (Item* item : player.GetInventory().GetItemList())
			{
				if (cmd == item->GetItemName() + L"ÀåÂø")
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
				if (cmd == weapon->GetItemName() + L"ÇØÁ¦")
				{
					HandleUnequipCommand(weapon->GetEquipType());
					return;
				}
			}

			if (const EquipableItem* armor = player.GetEquipment().GetArmor())
			{
				if (cmd == armor->GetItemName() + L"ÇØÁ¦")
				{
					HandleUnequipCommand(armor->GetEquipType());
					return;
				}
			}

			m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎ½ÄÇÒ ¼ö ¾ø´Â ¸í·ÉÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØ ÁÖ¼¼¿ä.");
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
	m_screen.Write(0, 0, L"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"¦¢");
		m_screen.Write(32, y, L"¦¢");
		m_screen.Write(126, y, L"¦¢");
	}

	m_screen.Write(13, 1, L"[ ´É·ÂÄ¡ ]");
	m_screen.Write(73, 1, L"<< ¸¶À» >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡");
	m_screen.Write(2, 3, L"ÀÌ¸§: " + player.GetName());
	m_screen.Write(2, 4, L"Á¤º¸: " + player.GetDescription());
	m_screen.Write(2, 5, L"·¹º§: " + to_wstring(player.GetExperience().m_level));
	m_screen.Write(2, 6, L"°æÇèÄ¡: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().m_currentExp));
	m_screen.Write(2, 7, L"°ñµå: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"°ø°Ý·Â: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"¹æ¾î·Â: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"¹ÎÃ¸: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"ÀåÂø ¾ÆÀÌÅÛ");
	m_screen.Write(2, 14, L"¹«±â: " + (player.GetEquipment().GetWeapon() == nullptr ? L"¹ÌÀåÂø" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 15, L"¹æ¾î±¸: " + (player.GetEquipment().GetArmor() == nullptr ? L"¹ÌÀåÂø" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 17, L"ÀÎº¥Åä¸® ");
	for (int i = 0; i < player.GetInventory().GetItemList().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItemList()[i]->GetItemName());
	}
	m_screen.Write(0, 29, L"¦¢¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¢");
	m_screen.Write(0, 30, L"¦¢"); m_screen.Write(2, 30, L"¸í·É > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"¦¢");
	m_screen.Write(0, 31, L"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");
}

void MainScene::ShowMainMenu()
{
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");
}

void MainScene::HandleHealCommand()
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	const uint16 playerMaxHP = player.GetStats().GetStatValue(EStatType::HP);

	if (player.GetCurrentHP() == playerMaxHP)
	{
		m_textPrompt.Enqueue({ L"Èú·¯ : ³Ê ÀÌ¹Ì Ã¼·ÂÀÌ ´Ù È¸º¹µÈ°Í °°¾Æ..." });
	}
	else if (player.GetGold().RemoveGold(500))
	{
		player.HealHp(playerMaxHP);
		m_textPrompt.Enqueue({ L"Èú·¯ : ³ÊÀÇ Ã¼·ÂÀ» ¸ðµÎ È¸º¹½ÃÄ×¾î!" });
	}
	else
	{
		m_textPrompt.Enqueue({ L"Èú·¯ : µ·ÀÌ ÀÖ¾î¾ß È¸º¹À» ½ÃÄÑÁÙ ¼ö ÀÖ¾î!" });
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
			m_textPrompt.Enqueue({ L"½Ã½ºÅÛ : ÀÎº¥Åä¸®¿¡ °ø°£ÀÌ ºÎÁ·ÇÕ´Ï´Ù." });
			m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
			return;
		}

		const EquipableItem* unequipItem = equipment.Unequip(equipType, stats);
		if (unequipItem == nullptr)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}

		if (inventory.AddItem(unequipItem) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}
	}

	if (equipment.Equip(equipItem, stats) == false)
	{
		m_textPrompt.Enqueue({ L"[¿À·ù] : »õ·Î¿î ¾ÆÀÌÅÛÀ» ÀåÂøÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
		return;
	}

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + equipItem->GetItemName() + L"] À»(¸¦) ÀåÂøÇß½À´Ï´Ù.");
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
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
		m_textPrompt.Enqueue({ L"½Ã½ºÅÛ : ÀÎº¥Åä¸®¿¡ °ø°£ÀÌ ºÎÁ·ÇÕ´Ï´Ù." });
		m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
		return;
	}

	const EquipableItem* unequipped = equipment.Unequip(equipType, stats);
	if (unequipped != nullptr || inventory.AddItem(unequipped) == true)
	{
		m_textPrompt.Enqueue(L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù.");
		return;
	}

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + unequipped->GetItemName() + L"] À»(¸¦) ÇØÁ¦Çß½À´Ï´Ù.");
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
	return;
}
