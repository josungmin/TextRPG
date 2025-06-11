#include "DungeonScene.h"
#include "../GameInstance.h"
//#include "../Stat/StatDataType.h"
#include "../Character/EnemyCharacter.h"
#include "MainScene.h"
#include "../CombatGameMode.h"

DungeonScene::DungeonScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3)
{
	m_currentSceneState = EDungeonSceneState::Default;

	StatContainer enemyStats;
	enemyStats.stats[EStatType::HP].baseValue = 50;
	enemyStats.stats[EStatType::AttackPower].baseValue = 10;
	enemyStats.stats[EStatType::Defence].baseValue = 5;
	enemyStats.stats[EStatType::Agility].baseValue = 5;
	m_enemy = new EnemyCharacter(L"Goblin", L"Goblin Soldier", enemyStats);
}

DungeonScene::~DungeonScene()
{

}

void DungeonScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");
	//m_textPrompt.Enqueue(L"�ý��� : ��� �������� �̵� �Ͻðڽ��ϱ�?");
	//m_textPrompt.Enqueue(L"�ý��� : 1.���� 2.�߾� 3, ������");
}

void DungeonScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void DungeonScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand())
	{
		std::wstring cmd = m_input.GetCommand();

		if (m_currentSceneState == EDungeonSceneState::Default)
		{
			if (cmd == L"1" || cmd == L"��" || cmd == L"����" || cmd == L"1.����" || cmd == L"1����" || cmd == L"1 ����")
			{
				
			}

			if (cmd == L"2" || cmd == L"��" || cmd == L"�߾�" || cmd == L"2.�߾�" || cmd == L"2�߾�" || cmd == L"2 �߾�")
			{

			}

			if (cmd == L"3" || cmd == L"��" || cmd == L"����" || cmd == L"������" || cmd == L"3.������" || cmd == L"3.����" || cmd == L"3.��" || cmd == L"3 ��" || cmd == L"3 ����" || cmd == L"3 ������" || cmd == L"3��" || cmd == L"3����" || cmd == L"3������")
			{

			}


			/*if (cmd == L"Combat")
			{
				m_textPrompt.Enqueue(L"System : The battle begins.");
			}
			else if (cmd == L"Runaway")
			{
				m_textPrompt.Enqueue(L"System : You run away from the enemy, but are attacked and your HP decreases.");

				Scene* mainScene = new MainScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
			}*/
		}
		else if (m_currentSceneState == EDungeonSceneState::Combat)
		{
			//GameMode.ProcessCombat(enemy);
		}
	}
}

void DungeonScene::Render()
{
	m_textPrompt.Render();

	// Frame
	m_screen.Write(0, 0, L"����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	for (int y = 1; y <= 26; ++y)
	{
		m_screen.Write(0, y, L"��");
		m_screen.Write(32, y, L"��");
		m_screen.Write(126, y, L"��");
	}

	m_screen.Write(13, 1, L"[ Stat ]");
	m_screen.Write(73, 1, L"<< Dungeon >>");

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
	m_screen.Write(2, 13, L"��: " + (player.GetEquipment().GetArmor() == nullptr ? L"������" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(0, 27, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	if (m_currentSceneState == EDungeonSceneState::Default)
	{
		m_screen.Write(2, 28, L"Command List : Combat, Runaway");
	}

	m_screen.Write(0, 28, L"��");                                                                                                  m_screen.Write(126, 28, L"��");
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"Command > " + m_input.GetInputBuffer());                                     m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}
