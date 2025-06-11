#include "MainScene.h"
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
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
}

void MainScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void MainScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand()) 
	{
		std::wstring cmd = m_input.GetCommand();

		if (m_currentSceneState == EMainSceneState::Default && cmd == L"Healer")
		{
			m_textPrompt.Enqueue(L"System : I approach Healer and talk to him.");
			m_textPrompt.Enqueue(L"Healer : Give me 500 gold and I'll restore your HP!");
			m_currentSceneState = EMainSceneState::Healer;
		}
		else if (m_currentSceneState == EMainSceneState::Default && cmd == L"Inventory")
		{
			PlayerCharacter& player = GameInstance::Instance().GetPlayer();

			Item* sword = GameInstance::Instance().GetItemTable().CreateItem(L"���ϱ� ��");
			if (sword != nullptr)
			{
				EquipableItem* equipableItem = dynamic_cast<EquipableItem*>(sword);
				if (equipableItem != nullptr)
				{
					player.GetEquipment().Equip(equipableItem, player.GetStats());
				}				
			}

			Item* armor = GameInstance::Instance().GetItemTable().CreateItem(L"���ϱ� ����");
			if (sword != nullptr)
			{
				EquipableItem* equipableItem = dynamic_cast<EquipableItem*>(armor);
				if (equipableItem != nullptr)
				{
					player.GetEquipment().Equip(equipableItem, player.GetStats());
				}
			}
		}
		else if (m_currentSceneState == EMainSceneState::Default && cmd == L"Dungeon")
		{
			Scene* dungeonScene = new DungeonScene(m_screen, m_input);
			GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
		}
		else if (m_currentSceneState == EMainSceneState::Healer)
		{
			if (cmd == L"Yes") 
			{
				if (GameInstance::Instance().GetPlayer().GetGold().RemoveGold(500))
				{
					GameInstance::Instance().GetPlayer().HealHp(UINT16_MAX);
					m_textPrompt.Enqueue({ L"Healer : I've restored all your HP!" });
				}
				else 
				{
					m_textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				}

				m_currentSceneState = EMainSceneState::Default;
			}
			else if (cmd == L"No")
			{
				m_textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				m_currentSceneState = EMainSceneState::Default;
			}
		}
		//TODO :����׿�
		else if (m_currentSceneState == EMainSceneState::Default && cmd == L"Damage")
		{
			GameInstance::Instance().GetPlayer().TakeDamage(20);
		}
	}
}

void MainScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	for (int y = 1; y <= 26; ++y)
	{
		m_screen.Write(0, y, L"��");
		m_screen.Write(32, y, L"��");
		m_screen.Write(126, y, L"��");
	}

	m_screen.Write(13, 1, L"[ Stat ]");
	m_screen.Write(73, 1, L"<< Village >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(2, 3, L"�̸�: " + player.GetName());
	m_screen.Write(2, 4, L"����: " + player.GetDescription());
	m_screen.Write(2, 5, L"���: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 6, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 7, L"���ݷ�: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 8, L"����: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 9, L"��ø: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 11, L"���� ������:");
	m_screen.Write(2, 12, L"����: " + (player.GetEquipment().GetWeapon() == nullptr ? L"������" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 13, L"��: " +(player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(2, 15, L"�κ��丮: ");
	m_screen.Write(2, 16, L"���ϱ� ��"); // TODO: ������ ��� ���
	m_screen.Write(0, 27, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	if (m_currentSceneState == EMainSceneState::Healer)
	{
		m_screen.Write(2, 28, L"Command List : Yes, No");
	}
	else if (m_currentSceneState == EMainSceneState::Default)
	{
		m_screen.Write(2, 28, L"Command List : Healer, Shop, Dungeon, Inventory");
	}

	m_screen.Write(0, 28, L"��");                                                                                                  m_screen.Write(126, 28, L"��");
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"Command > " + m_input.GetInputBuffer());                                     m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	m_textPrompt.Render();
}
