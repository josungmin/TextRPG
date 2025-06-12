#include "DungeonScene.h"
#include "../GameInstance.h"
#include "../Character/EnemyCharacter.h"
#include "MainScene.h"


DungeonScene::DungeonScene(Screen& screen, Input& input)
	:Scene(screen, input), m_textPrompt(screen, 34, 3), m_combatGameMode(m_textPrompt)
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

	m_textPrompt.Enqueue(L"衛蝶蠱 : 湍瞪縑 殮濰м棲棻.");
	m_textPrompt.Enqueue(L"衛蝶蠱 : 湍瞪縑 菟橫憮濠 瞳擊 葆輿м棲棻.");
	m_textPrompt.Enqueue(L"衛蝶蠱 : 1.諄遴棻 2.紫蜂除棻");
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
			if (cmd == L"1" || cmd == L"諄遴棻" || cmd == L"1.諄遴棻")
			{
				m_combatGameMode.SetEnemy(*m_enemy);				
				m_currentSceneState = EDungeonSceneState::Combat;

				m_combatGameMode.ProcessCombat();
			}
			else if (cmd == L"2" || cmd == L"紫蜂" || cmd == L"紫蜂除棻" || cmd == L"1.紫蜂除棻")
			{
				Scene* mainScene = new MainScene(m_screen, m_input);
				GameInstance::Instance().GetSceneManager().ChangeScene(*mainScene);
			}
		}

		if (m_currentSceneState == EDungeonSceneState::Combat)
		{
			
		}
	}
}

void DungeonScene::Render()
{
	m_textPrompt.Render();

	// Frame
	m_screen.Write(0, 0, L"忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖");

	for (int y = 1; y <= 28; ++y)
	{
		m_screen.Write(0, y, L"弛");
		m_screen.Write(32, y, L"弛");
		m_screen.Write(126, y, L"弛");
	}

	m_screen.Write(13, 1, L"[ 棟溘纂 ]");
	m_screen.Write(73, 1, L"<< 湍瞪 >>");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_screen.Write(1, 2, L"式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式");
	m_screen.Write(2, 3, L"檜葷: " + player.GetName());
	m_screen.Write(2, 4, L"薑爾: " + player.GetDescription());
	m_screen.Write(2, 5, L"埤萄: " + to_wstring(player.GetGold().m_amount));
	m_screen.Write(2, 6, L"HP: " + to_wstring(player.GetStats().GetStatValue(EStatType::HP)) + L"/" + to_wstring(player.GetCurrentHP()));
	m_screen.Write(2, 7, L"奢問溘: " + to_wstring(player.GetStats().GetStatValue(EStatType::AttackPower)));
	m_screen.Write(2, 8, L"寞橫溘: " + to_wstring(player.GetStats().GetStatValue(EStatType::Defence)));
	m_screen.Write(2, 9, L"團繪: " + to_wstring(player.GetStats().GetStatValue(EStatType::Agility)));
	m_screen.Write(2, 11, L"濰雜 嬴檜蠱");
	m_screen.Write(2, 12, L"鼠晦: " + (player.GetEquipment().GetWeapon() == nullptr ? L"嘐濰雜" : player.GetEquipment().GetWeapon()->GetItemName()));
	m_screen.Write(2, 13, L"寞橫掘: " + (player.GetEquipment().GetArmor() == nullptr ? L"嘐濰雜" : player.GetEquipment().GetArmor()->GetItemName()));
	m_screen.Write(0, 29, L"弛式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式弛");
	m_screen.Write(0, 30, L"弛"); m_screen.Write(2, 30, L"Command > " + m_input.GetInputBuffer());                                     m_screen.Write(126, 30, L"弛");
	m_screen.Write(0, 31, L"戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎");
}
