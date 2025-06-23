#include "DungeonScene.h"
#include "../GameInstance.h"
#include "../Character/EnemyCharacter.h"
#include "MainScene.h"


DungeonScene::DungeonScene(Screen& screen, Input& input, TextPrompt& textPrompt)
	:Scene(screen, input, textPrompt), m_combatGameMode(m_textPrompt)
{
	m_currentSceneState = EDungeonSceneState::Default;

	StatContainer enemyStats;
	enemyStats.stats[EStatType::HP].baseValue = 50;
	enemyStats.stats[EStatType::AttackPower].baseValue = 10;
	enemyStats.stats[EStatType::Defence].baseValue = 5;
	enemyStats.stats[EStatType::Agility].baseValue = 5;
	m_enemy = new EnemyCharacter(L"���", L"��� ����", 10, 5, enemyStats);
}

DungeonScene::~DungeonScene()
{
	delete m_enemy;
}

void DungeonScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�. ������ ���� ���� �����մϴ�.");
	m_textPrompt.Enqueue(L"�ý��� : 1.�ο�� 2.��������");
}

void DungeonScene::OnExit()
{
	m_screen.Clear();
	m_textPrompt.Clear();
}

void DungeonScene::Update()
{
	m_textPrompt.Update();

	if (m_input.HasCommand() == true)
	{
		const wstring cmd = m_input.GetCommand(); 

		if (m_currentSceneState == EDungeonSceneState::Default)
		{
			if (cmd == L"1" || cmd == L"�ο��" || cmd == L"1.�ο��")
			{
				m_combatGameMode.SetEnemy(m_enemy);
				m_currentSceneState = EDungeonSceneState::Combat;
			}
			else if (cmd == L"2" || cmd == L"����" || cmd == L"��������" || cmd == L"1.��������")
			{
				Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
				GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
			}
			else
			{
				m_textPrompt.Enqueue(L"�ý��� : �� �� ���� ����Դϴ�. �ٽ� �Է����ּ���.");
			}
		}
		else if (m_currentSceneState == EDungeonSceneState::Combat)
		{
			m_combatGameMode.SetPlayerCommand(cmd);
		}

		if (m_currentSceneState == EDungeonSceneState::ContinueCombat)
		{
			if (cmd == L"1" || cmd == L"�̵�" || cmd == L"1.�̵�" || cmd == L"1�̵�")
			{
				Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
				GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
			}
		}
	}

	if (m_currentSceneState == EDungeonSceneState::Combat)
	{
		m_combatGameMode.ProcessCombat();

		if (m_combatGameMode.IsCombatEnd() == true)
		{
			m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�. ������ �̵��մϴ�.");
			m_textPrompt.Enqueue(L"�ý��� : 1.�̵�");
			m_currentSceneState = EDungeonSceneState::ContinueCombat;
		}
	}
}


void DungeonScene::Render()
{
	// Frame
	m_screen.Write(0, 0, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"��");
		m_screen.Write(32, y, L"��");
		m_screen.Write(126, y, L"��");
	}

	m_screen.Write(13, 1, L"[ �ɷ�ġ ]");
	m_screen.Write(73, 1, L"<< �κ��丮 >>");

	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();
	m_screen.Write(1, 2, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(2, 3, L"�̸�: " + player.GetName());
	m_screen.Write(2, 4, L"����: " + player.GetDescription());
	m_screen.Write(2, 5, L"����: " + to_wstring(player.GetExperience().level));
	m_screen.Write(2, 6, L"����ġ: " + to_wstring(player.GetExperience().GetRequiredExpForNextLevel()) + L"/" + to_wstring(player.GetExperience().currentExp));
	m_screen.Write(2, 7, L"���: " + to_wstring(player.GetGold().amount));
	m_screen.Write(2, 8, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 9, L"���ݷ�: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 10, L"����: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 11, L"��ø: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 13, L"���� ������");
	m_screen.Write(2, 14, L"����: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon) == nullptr ? L"������" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Weapon)->GetItemName())));
	m_screen.Write(2, 15, L"��: " + (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::Armor) == nullptr ? L"������" : (player.GetEquipment().GetEquipedItem(EquipableItem::EEquipType::
		Armor)->GetItemName())));
	m_screen.Write(2, 17, L"�κ��丮 ");
	const vector<ItemInstance>& itemList = player.GetInventory().GetItemList();
	for (int i = 0; i < itemList.size(); ++i)
	{
		m_screen.Write(2, 18 + i, itemList[i].Get()->GetItemName());
	}
	m_screen.Write(0, 29, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	m_screen.Write(0, 30, L"��"); m_screen.Write(2, 30, L"��� > " + m_input.GetInputBuffer());
	m_screen.Write(126, 30, L"��");
	m_screen.Write(0, 31, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}
