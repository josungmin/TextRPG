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
	m_enemy = new EnemyCharacter(L"고블린", L"고블린 병사", 10, 5, enemyStats);
}

DungeonScene::~DungeonScene()
{
	delete m_enemy;
}

void DungeonScene::OnEnter()
{
	m_screen.Clear();
	m_textPrompt.Clear();

	m_textPrompt.Enqueue(L"시스템 : 던전에 입장합니다. 던전에 들어서자 적을 마주합니다.");
	m_textPrompt.Enqueue(L"시스템 : 1.싸운다 2.도망간다");
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
			if (cmd == L"1" || cmd == L"싸운다" || cmd == L"1.싸운다")
			{
				m_combatGameMode.SetEnemy(m_enemy);
				m_currentSceneState = EDungeonSceneState::Combat;
			}
			else if (cmd == L"2" || cmd == L"도망" || cmd == L"도망간다" || cmd == L"1.도망간다")
			{
				Scene* mainScene = new MainScene(m_screen, m_input, m_textPrompt);
				GameInstance::GetInstance().GetSceneManager().ChangeScene(*mainScene);
			}
			else
			{
				m_textPrompt.Enqueue(L"시스템 : 알 수 없는 명령입니다. 다시 입력해주세요.");
			}
		}
		else if (m_currentSceneState == EDungeonSceneState::Combat)
		{
			m_combatGameMode.SetPlayerCommand(cmd);
		}

		if (m_currentSceneState == EDungeonSceneState::ContinueCombat)
		{
			if (cmd == L"1" || cmd == L"이동" || cmd == L"1.이동" || cmd == L"1이동")
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
			m_textPrompt.Enqueue(L"시스템 : 전투를 종료합니다. 마을로 이동합니다.");
			m_textPrompt.Enqueue(L"시스템 : 1.이동");
			m_currentSceneState = EDungeonSceneState::ContinueCombat;
		}
	}
}


void DungeonScene::Render()
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
