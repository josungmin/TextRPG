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

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎº¥Åä¸®¸¦ ¿±´Ï´Ù.");
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
				if (cmd == L"1" || cmd == L"ÀåÂø" || cmd == L"¾ÆÀÌÅÛÀåÂø" || cmd == L"1.¾ÆÀÌÅÛÀåÂø")
				{
					EnableEquipMenu();
					m_currentScene = EInventorySceneState::Equip;
				}
				else if (cmd == L"2" || cmd == L"ÇØÁ¦" || cmd == L"¾ÆÀÌÅÛÇØÁ¦" || cmd == L"1.¾ÆÀÌÅÛÇØÁ¦")
				{
					EnableUnequipMenu();
					m_currentScene = EInventorySceneState::Unequip;
				}
				else if (cmd == L"3" || cmd == L"³ª°¡±â")
				{
					Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
					GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
				}
				else
				{
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎ½ÄÇÒ ¼ö ¾ø´Â ¸í·ÉÀÔ´Ï´Ù. ´Ù½Ã ÀÔ·ÂÇØ ÁÖ¼¼¿ä.");
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
	m_screen.Write(0, 0, L"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"¦¢");
		m_screen.Write(32, y, L"¦¢");
		m_screen.Write(126, y, L"¦¢");
	}

	m_screen.Write(13, 1, L"[ ´É·ÂÄ¡ ]");
	m_screen.Write(73, 1, L"<< ÀÎº¥Åä¸® >>");

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

void InventoryScene::EnableInventoryMenu()
{
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.¾ÆÀÌÅÛ ÀåÂø 2.¾ÆÀÌÅÛ ÇØÁ¦ 3.³ª°¡±â");
}

void InventoryScene::EnableEquipMenu()
{	
	const vector<Item*>& inventoryItems = GameInstance::Instance().GetPlayer().GetInventory().GetItemList();

	if (inventoryItems.size() == 0)
	{
		m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀåÂøÇÒ ¾ÆÀÌÅÛÀÌ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.");
		EnableInventoryMenu();
		m_currentScene = EInventorySceneState::Default;
		return;
	}

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² ¾ÆÀÌÅÛÀ» [ÀåÂø] ÇÏ½Ã°Ú½À´Ï±î? ¹øÈ£¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä.");
	for (uint8 i = 0; i < inventoryItems.size(); i++)
	{
		m_textPrompt.Enqueue(L"ÀÎº¥Åä¸® : [" + to_wstring(i) + L"] " + inventoryItems[i]->GetItemName());
	}
}

void InventoryScene::EnableUnequipMenu()
{
	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	Equipment& equipment = player.GetEquipment();

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² ¾ÆÀÌÅÛÀ» [ÇØÁ¦] ÇÏ½Ã°Ú½À´Ï±î? ¹øÈ£¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä.");
	m_textPrompt.Enqueue(L"ÀÎº¥Åä¸® : [0]" + (equipment.GetWeapon() == nullptr ? L"ºñ¾îÀÖÀ½" : equipment.GetWeapon()->GetItemName()));
	m_textPrompt.Enqueue(L"ÀÎº¥Åä¸® : [1]" + (equipment.GetArmor() == nullptr ? L"ºñ¾îÀÖÀ½" : equipment.GetArmor()->GetItemName()));
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
		m_textPrompt.Enqueue({ L"[½Ã½ºÅÛ] : Àß¸øµÈ ¹øÈ£¸¦ ÀÔ·ÂÇß½À´Ï´Ù." });
		return;
	}

	const EquipableItem* targetItem = dynamic_cast<EquipableItem*>(inventory.GetItemList()[index]);
	if (targetItem == nullptr)
	{
		m_textPrompt.Enqueue({ L"½Ã½ºÅÛ : ÀåÂøÇÒ ¼ö ÀÖ´Â ¾ÆÀÌÅÛÀÌ ¾Æ´Õ´Ï´Ù." });
		return;
	}
		
	if (equipment.IsEquiped(targetItem->GetEquipType()) == true)
	{
		if (inventory.IsFull() == true)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			m_textPrompt.Enqueue({ L"[½Ã½ºÅÛ] : ÀÎº¥Åä¸® °ø°£ÀÌ ºÎÁ·ÇÕ´Ï´Ù." });
			return;
		}

		const EquipableItem* unequipItem = dynamic_cast<EquipableItem*>(equipment.GetWeapon()->Clone());
		if (unequipItem == nullptr)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			delete unequipItem;
			return;
		}

		if (inventory.AddItem(unequipItem) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			delete unequipItem;
			return;
		}

		delete unequipItem;
		return;
	}

	if (inventory.RemoveItem(targetItem->GetItemName()) == false)
	{
		m_textPrompt.Enqueue({ L"[¿À·ù] : »õ·Î¿î ¾ÆÀÌÅÛÀ» ÀåÂøÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
		return;
	}

	if (equipment.Equip(targetItem, stats) == false)
	{
		m_textPrompt.Enqueue({ L"[¿À·ù] : »õ·Î¿î ¾ÆÀÌÅÛÀ» ÀåÂøÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
		return;
	}

	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + targetItem->GetItemName() + L"] À»(¸¦) ÀåÂøÇß½À´Ï´Ù.");

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
		m_textPrompt.Enqueue({ L"[½Ã½ºÅÛ] : ÀÎº¥Åä¸® °ø°£ÀÌ ºÎÁ·ÇÕ´Ï´Ù." });
		EnableInventoryMenu();
		m_currentScene = EInventorySceneState::Default;
	}

	const uint8 index = static_cast<uint8>(stoi(cmd));
	if (index == 0)
	{
		const EquipableItem* unequipedItem = equipment.GetWeapon();

		if (inventory.AddItem(unequipedItem) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}

		if (equipment.Unequip(unequipedItem->GetEquipType(), stats) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}

		m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + unequipedItem->GetItemName() + L"] À»(¸¦) ÇØÁ¦Çß½À´Ï´Ù.");

	}
	else if (index == 1)
	{
		const EquipableItem* unequipedItem = equipment.GetArmor();

		if (inventory.AddItem(unequipedItem) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}

		if (equipment.Unequip(unequipedItem->GetEquipType(), stats) == false)
		{
			m_textPrompt.Enqueue({ L"[¿À·ù] : ±âÁ¸ ¾ÆÀÌÅÛÀ» ÇØÁ¦ÇÏ´Âµ¥ ¹®Á¦°¡ ¹ß»ýÇß½À´Ï´Ù." });
			return;
		}

		m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + unequipedItem->GetItemName() + L"] À»(¸¦) ÇØÁ¦Çß½À´Ï´Ù.");

		delete unequipedItem;
	}
	else
	{
		m_textPrompt.Enqueue({ L"[½Ã½ºÅÛ] : Àß¸øµÈ ¹øÈ£¸¦ ÀÔ·ÂÇß½À´Ï´Ù." });
		return;
	}

	EnableInventoryMenu();
	m_currentScene = EInventorySceneState::Default;
	return;
}
