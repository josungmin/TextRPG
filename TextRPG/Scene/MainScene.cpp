#include "MainScene.h"
#include "../GameInstance.h"
#include "../Character/PlayerCharacter.h"
#include "DungeonScene.h"

MainScene::MainScene(Screen& screen, Input& input)
	:Scene(screen, input), textPrompt(screen, 34, 3)
{
	CurrentSceneState = EMainSceneState::Default;
}

MainScene::~MainScene()
{
}

void MainScene::OnEnter()
{
	m_screen.Clear();
	textPrompt.Clear();
}

void MainScene::OnExit()
{
	m_screen.Clear();
	textPrompt.Clear();
}

void MainScene::Update()
{
	textPrompt.Update();

	if (m_input.HasCommand()) 
	{
		std::wstring cmd = m_input.GetCommand();

		if (CurrentSceneState == EMainSceneState::Default && cmd == L"Healer")
		{
			textPrompt.Enqueue(L"System : I approach Healer and talk to him.");
			textPrompt.Enqueue(L"Healer : Give me 500 gold and I'll restore your HP!");
			CurrentSceneState = EMainSceneState::Healer;
		}
		else if (CurrentSceneState == EMainSceneState::Default && cmd == L"Inventory")
		{
			PlayerCharacter& player = GameInstance::Instance().GetPlayer();

			auto sword = dynamic_pointer_cast<EquipableItem>(GameInstance::Instance().GetItemTable().CreateItem(L"Sword"));
			if (sword != nullptr)
			{
				player.GetEquipment().Equip(sword, player.GetStats());
			}

			auto armor = dynamic_pointer_cast<EquipableItem>(GameInstance::Instance().GetItemTable().CreateItem(L"Armor"));
			if (armor != nullptr)
			{
				player.GetEquipment().Equip(armor, player.GetStats());
			}
		}
		else if (CurrentSceneState == EMainSceneState::Default && cmd == L"Dungeon")
		{
			Scene* dungeonScene = new DungeonScene(m_screen, m_input);
			GameInstance::Instance().GetSceneManager().ChangeScene(*dungeonScene);
		}
		else if (CurrentSceneState == EMainSceneState::Healer)
		{
			if (cmd == L"Yes") 
			{
				if (GameInstance::Instance().GetPlayer().GetGold().RemoveGold(500))
				{
					GameInstance::Instance().GetPlayer().HealHp(UINT16_MAX);
					textPrompt.Enqueue({ L"Healer : I've restored all your HP!" });
				}
				else 
				{
					textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				}

				CurrentSceneState = EMainSceneState::Default;
			}
			else if (cmd == L"No")
			{
				textPrompt.Enqueue({ L"Healer : I don't have enough money..." });
				CurrentSceneState = EMainSceneState::Default;
			}
		}
		//TODO :����׿�
		else if (CurrentSceneState == EMainSceneState::Default && cmd == L"Damage")
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
	m_screen.Write(2, 11, L"���� ������");
	m_screen.Write(2, 12, L"����: " + (player.GetEquipment().GetWeapon() == nullptr ? L"������" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 13, L"��: " +(player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(0, 27, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	if (CurrentSceneState == EMainSceneState::Healer)
	{
		m_screen.Write(2, 28, L"Command List : Yes, No");
	}
	else if (CurrentSceneState == EMainSceneState::Default)
	{
		m_screen.Write(2, 28, L"Command List : Healer, Shop, Dungeon, Inventory");
	}

	m_screen.Write(0, 28, L"��");                                                                                                  m_screen.Write(126, 28, L"��");
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"Command > " + m_input.GetInputBuffer());                                     m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	textPrompt.Render();
}
