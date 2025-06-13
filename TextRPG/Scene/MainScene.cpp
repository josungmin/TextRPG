#include "MainScene.h"
#include <string>
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "ShopScene.h"
#include "DungeonScene.h"


MainScene::MainScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3)
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
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
	m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");
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

		if (m_currentSceneState == EMainSceneState::Default)
		{
			//m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
			//m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");

			if (cmd == L"1" || cmd == L"Èú·¯" || cmd == L"1.Èú·¯" || cmd == L"1Èú·¯" || cmd == L"Èú")
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : Èú·¯¿¡°Ô ´Ù°¡°¡ ¸»À» °Ì´Ï´Ù.");
				m_textPrompt.Enqueue(L"Èú·¯ : 500°ñµå¸¦ ÁÖ¸é ³ÊÀÇ Ã¼·ÂÀ» ¸ðµÎ È¸º¹½ÃÄÑ ÁÙ°Ô!");
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.¼ö¶ôÇÑ´Ù 2.°ÅÀýÇÑ´Ù");
				m_currentSceneState = EMainSceneState::Healer;
			}
			else if (cmd == L"2" || cmd == L"»óÁ¡" || cmd == L"2.»óÁ¡" || cmd == L"2»óÁ¡")
			{
				Scene* shopScene = new ShopScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*shopScene);
			}
			else if (cmd == L"3" || cmd == L"ÀÎº¥" || cmd == L"ÀÎº¥Åä¸®" || cmd == L"3.ÀÎº¥" || cmd == L"3ÀÎº¥" || cmd == L"3ÀÎº¥Åä¸®" || cmd == L"3.ÀÎº¥Åä¸®")
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø', '¾ÆÀÌÅÛ¸í ÇØÁ¦' È¤Àº 'Ãë¼Ò'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
				m_currentSceneState = EMainSceneState::Inventory;
			}
			else if (cmd == L"4" || cmd == L"´øÀü" || cmd == L"4´øÀü" || cmd == L"4.´øÀü")
			{
				Scene* dungeonScene = new DungeonScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
			}
		}
		else if (m_currentSceneState == EMainSceneState::Healer)
		{
			if (cmd == L"1" || cmd == L"¼ö¶ô" || cmd == L"¼ö¶ôÇÑ´Ù" || cmd == L"1.¼ö¶ô" || cmd == L"1¼ö¶ô" || cmd == L"1¼ö¶ôÇÑ´Ù" || cmd == L"1.¼ö¶ôÇÑ´Ù")
			{
				PlayerCharacter player = GameInstance::Instance().GetPlayer();

				if (player.GetCurrentHP() == player.GetStats().GetStatValue(EStatType::HP))
				{
					m_textPrompt.Enqueue({ L"Èú·¯ : ³Ê ÀÌ¹Ì Ã¼·ÂÀÌ ´Ù È¸º¹µÈ°Í °°¾Æ..." });
				}
				else if (GameInstance::Instance().GetPlayer().GetGold().RemoveGold(500))
				{
					GameInstance::Instance().GetPlayer().HealHp(UINT16_MAX);
					m_textPrompt.Enqueue({ L"Èú·¯ : ³ÊÀÇ Ã¼·ÂÀ» ¸ðµÎ È¸º¹½ÃÄ×¾î!" });
				}
				else
				{
					m_textPrompt.Enqueue({ L"Èú·¯ : ³Ê µ·ÀÌ ºÎÁ·ÇÏ±¸³ª..." });
				}

				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");
				m_currentSceneState = EMainSceneState::Default;
			}
			else if (cmd == L"2" || cmd == L"°ÅÀý" || cmd == L"°ÅÀýÇÑ´Ù" || cmd == L"1.°ÅÀý" || cmd == L"1°ÅÀý" || cmd == L"1°ÅÀýÇÑ´Ù" || cmd == L"1.°ÅÀýÇÑ´Ù")
			{
				m_textPrompt.Enqueue({ L"Èú·¯ : ³Ê µ·ÀÌ ºÎÁ·ÇÏ±¸³ª..." });
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");
				m_currentSceneState = EMainSceneState::Default;
			}
		}
		else if (m_currentSceneState == EMainSceneState::Inventory)
		{
			PlayerCharacter& player = GameInstance::Instance().GetPlayer();
			const vector<Item*>& items = player.GetInventory().GetItems();

			if (cmd == L"³ª°¡±â")
			{
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ¾î¶² Çàµ¿À» ÇÏ½Ã°Ú½À´Ï±î?");
				m_textPrompt.Enqueue(L"½Ã½ºÅÛ : 1.È¸º¹ 2.»óÁ¡ 3.ÀÎº¥Åä¸® 4.´øÀü");
				m_currentSceneState = EMainSceneState::Default;
				return;
			}

			for (Item* item : items)
			{
				if (item == nullptr || item->GetType() != EItemType::Equip)
				{
					continue;
				}

				const wstring name = item->GetItemName();
				if (cmd == name + L" ÀåÂø")
				{
					EquipableItem* equip = dynamic_cast<EquipableItem*>(item);
					if (equip == nullptr)
					{
						m_textPrompt.Enqueue(L"[¿À·ù] : [" + name + L"] Àº ÀåÂø °¡´ÉÇÑ ¾ÆÀÌÅÛÀÌ ¾Æ´Õ´Ï´Ù.");
						continue;
					}

					player.GetEquipment().Equip(equip, player.GetStats());
					player.GetInventory().RemoveItem(equip->GetItemName());
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + name + L"] À»(¸¦) ÀåÂøÇß½À´Ï´Ù.");
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
					return;
				}
				else if (cmd == name + L" ÇØÁ¦")
				{
					const EquipableItem* equip = dynamic_cast<EquipableItem*>(item);
					if (equip == nullptr)
					{
						m_textPrompt.Enqueue(L"[¿À·ù] : [" + name + L"] Àº ÇØÁ¦ °¡´ÉÇÑ ¾ÆÀÌÅÛÀÌ ¾Æ´Õ´Ï´Ù.");
						continue;
					}

					player.GetEquipment().Unequip(equip->GetEquipType(), player.GetStats());
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : [" + name + L"] À»(¸¦) ÇØÁ¦Çß½À´Ï´Ù.");
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
					return;
				}
				else
				{
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : ÀÎ½ÄÇÒ ¼ö ¾ø´Â ¸í·ÉÀÔ´Ï´Ù.");
					m_textPrompt.Enqueue(L"½Ã½ºÅÛ : '¾ÆÀÌÅÛ¸í ÀåÂø' ¶Ç´Â '¾ÆÀÌÅÛ¸í ÇØÁ¦'¸¦ ÀÔ·ÂÇÏ°Å³ª, '³ª°¡±â'¸¦ ÀÔ·ÂÇÏ¼¼¿ä.");
				}
			}
		}
	}
}

void MainScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤");

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
	for (int i = 0; i < player.GetInventory().GetItems().size(); ++i)
	{
		m_screen.Write(2, 18 + i, player.GetInventory().GetItems()[i]->GetItemName());
	}
	m_screen.Write(0, 29, L"¦¢¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¢");
	m_screen.Write(0, 30, L"¦¢"); m_screen.Write(2, 30, L"¸í·É > " + m_input.GetInputBuffer());                                    
	m_screen.Write(126, 30, L"¦¢");
	m_screen.Write(0, 31, L"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥");

	m_textPrompt.Render();
}
