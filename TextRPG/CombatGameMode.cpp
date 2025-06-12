#include "CombatGameMode.h"
#include <memory>

#include "GameInstance.h"
#include "Stat/StatDataType.h"
#include "Character/PlayerCharacter.h"
#include "Character/EnemyCharacter.h"
#include "TextPrompt.h"
#include "Scene/TitleScene.h"

CombatGameMode::CombatGameMode(TextPrompt& textPrompt)
	: m_textPrompt(textPrompt), m_enemy(nullptr)
{
	currentCombatState = ECombatState::CombatStart;
}

CombatGameMode::~CombatGameMode()
{
	delete m_enemy;
}

void CombatGameMode::ProcessCombat()
{
	if (m_enemy == nullptr)
	{
		return;
	}

	switch (currentCombatState)
	{
		case ECombatState::PlayerInput:
		{
			
			break;
		}
		case ECombatState::CombatStart:
		{
			CombatStart();
			break;
		}
		case ECombatState::CombatEnd:
		{
			CombatEnd();
			break;
		}			
		case ECombatState::PlayerAction:
		{
			PlayerAction();
			break;
		}
		case ECombatState::EnemyAction:
		{
			EnemyAction();
			break;
		}
		default:
		{
			break;
		}
	}
}

void CombatGameMode::SetEnemy(EnemyCharacter& newEnemy)
{
	if (m_isCombat == true)
	{
		return;
	}

	if (m_enemy != nullptr)
	{
		delete m_enemy;
	}

	m_enemy = &newEnemy;
}

void CombatGameMode::CombatStart()
{
	if (m_enemy == nullptr)
	{
		return;
	}

	m_isCombat = true;
	m_textPrompt.Enqueue(L"시스템 : 전투를 시작합니다.");

	uint16_t playerAgility = GameInstance::Instance().GetPlayer().GetStats().GetStatValue(EStatType::Agility);
	uint16_t enemyAgility = m_enemy->GetStats().GetStatValue(EStatType::Agility);

	currentCombatState = playerAgility < enemyAgility ? ECombatState::EnemyAction : ECombatState::PlayerAction;
}

void CombatGameMode::PlayerAction()
{
	m_textPrompt.Enqueue(L"시스템 : 플레이어가 공격합니다.");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	m_enemy->TakeDamage(player.GetStats().GetStatValue(EStatType::AttackPower));

	m_textPrompt.Enqueue(L"시스템 : 적 캐릭터 HP " + to_wstring(m_enemy->GetCurrentHP()));
	
	if (m_enemy->GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 적 캐릭터를 처치했습니다.");
		currentCombatState = ECombatState::CombatEnd;
	}

	currentCombatState = ECombatState::EnemyAction;
}

void CombatGameMode::EnemyAction()
{
	m_textPrompt.Enqueue(L"시스템 : 적 캐릭터가 공격합니다.");

	PlayerCharacter& player = GameInstance::Instance().GetPlayer();
	player.TakeDamage(m_enemy->GetStats().GetStatValue(EStatType::AttackPower));

	m_textPrompt.Enqueue(L"시스템 : 플레이어 캐릭터 HP " + to_wstring(player.GetCurrentHP()));

	if (player.GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 플레이어 캐릭터가 사망했습니다.");
		currentCombatState = ECombatState::CombatEnd;
	}

	currentCombatState = ECombatState::PlayerAction;
}

void CombatGameMode::CombatEnd()
{
	m_isCombat = false;
	m_textPrompt.Enqueue(L"시스템 : 전투를 종료합니다.");
}
