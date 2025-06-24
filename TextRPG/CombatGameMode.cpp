#include "CombatGameMode.h"
#include "GameInstance.h"
#include "Stat/StatDataType.h"
#include "Character/PlayerCharacter.h"
#include "Character/EnemyCharacter.h"
#include "TextPrompt.h"
#include "Scene/TitleScene.h"

CombatGameMode::CombatGameMode(TextPrompt& textPrompt)
	: m_textPrompt(textPrompt), m_enemy(nullptr)
{
	m_currentCombatState = ECombatState::CombatStart;
}

CombatGameMode::~CombatGameMode()
{

}

void CombatGameMode::ProcessCombat()
{
	if (m_enemy == nullptr)
	{
		return;
	}

	switch (m_currentCombatState)
	{
		case ECombatState::WaitForPlayerInput:
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

void CombatGameMode::SetEnemy(EnemyCharacter* newEnemy)
{
	if (newEnemy == nullptr)
	{
		return;
	}

	m_enemy = newEnemy;
	m_currentCombatState = ECombatState::CombatStart;
	m_isCombatEnded = false;
}

void CombatGameMode::SetPlayerCommand(const wstring& command)
{
	if (m_currentCombatState != ECombatState::WaitForPlayerInput)
	{
		return;
	}

	m_command = command;
	m_currentCombatState = ECombatState::PlayerAction;
}

void CombatGameMode::CombatStart()
{
	if (m_enemy == nullptr)
	{
		return;
	}

	m_isCombatEnded = false;
	m_textPrompt.Enqueue(L"시스템 : 전투를 시작합니다.");

	const uint16 playerAgility = GameInstance::GetInstance().GetPlayer().GetStats().GetStatValue(EStatType::Agility);
	const uint16 enemyAgility = m_enemy->GetStats().GetStatValue(EStatType::Agility);

	if (playerAgility >= enemyAgility)
	{
		m_textPrompt.Enqueue(L"시스템 : 플레이어가 공격합니다. 어떤 행동을 하시겠습니까?");
		m_textPrompt.Enqueue(L"시스템 : 1.공격 2.회복");
		m_currentCombatState = ECombatState::WaitForPlayerInput;
		return;
	}
	else
	{
		m_textPrompt.Enqueue(L"시스템 : 적 캐릭터가 공격합니다.");
		m_currentCombatState = ECombatState::EnemyAction;
		return;
	}
}

void CombatGameMode::PlayerAction()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

	if (m_command == L"1" || m_command == L"공격" || m_command == L"1공격" || m_command == L"1.공격")
	{
		const uint16 damage = player.GetStats().GetStatValue(EStatType::AttackPower);
		m_enemy->TakeDamage(damage);

		m_textPrompt.Enqueue(L"플레이어 : [" + m_enemy->GetName() + L"]" + L"에게 " + to_wstring(damage) + L" 피해를 입혔습니다. 현재 적 HP " + std::to_wstring(m_enemy->GetCurrentHP()));
	}
	else if (m_command == L"2" || m_command == L"회복" || m_command == L"2회복" || m_command == L"2.회복")
	{
		const uint16 amount = 10;
		player.HealHp(amount);
		m_textPrompt.Enqueue(L"플레이어 : HP를 " + std::to_wstring(amount) + L" 회복했습니다.");
	}
	else
	{
		m_textPrompt.Enqueue(L"시스템 : 잘못된 명령입니다. 다시 선택하세요.");
		m_currentCombatState = ECombatState::WaitForPlayerInput;
		return;
	}

	m_command.clear();

	if (m_enemy->GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 적을 처치했습니다!");
		m_currentCombatState = ECombatState::CombatEnd;
		return;
	}
	else
	{
		m_currentCombatState = ECombatState::EnemyAction;
		return;
	}
}

void CombatGameMode::EnemyAction()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

	const uint16 damage = m_enemy->GetStats().GetStatValue(EStatType::AttackPower);
	player.TakeDamage(damage);

	m_textPrompt.Enqueue(m_enemy->GetName() + L" : " + L"[" + player.GetName() + L"]" + L"에게 " + to_wstring(damage) + L" 피해를 입혔습니다. 현재 플레이어 HP " + std::to_wstring(player.GetCurrentHP()));

	if (player.GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"시스템 : 당신은 쓰러졌습니다...");
		m_currentCombatState = ECombatState::CombatEnd;
		return;
	}
	else
	{
		m_textPrompt.Enqueue(L"시스템 : 플레이어가 공격합니다. 어떤 행동을 하시겠습니까?");
		m_textPrompt.Enqueue(L"시스템 : 1.공격 2.회복");
		m_currentCombatState = ECombatState::WaitForPlayerInput;
		return;
	}
}

void CombatGameMode::CombatEnd()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

	if (player.GetIsDead() == true)
	{
		m_isCombatEnded = true;
		return;
	}

	const int8 dropExp = m_enemy->GetDropExp();
	player.GetExperience().AddExperience(dropExp);
	m_textPrompt.Enqueue(L"시스템 : " + std::to_wstring(dropExp) + L" 경험치를 획득했습니다.");

	const uint16 dropGold = m_enemy->GetDropGold();
	player.GetGold().AddGold(dropGold);
	m_textPrompt.Enqueue(L"시스템 : " + std::to_wstring(dropGold) + L" 골드를 획득했습니다.");

	const vector<wstring>& dropItems = m_enemy->GetDropItems();
	const uint64 randNum = rand() % dropItems.size();

	const Item* dropItem = GameInstance::GetInstance().GetItemTable().CreateItem(dropItems[randNum]);
	if (dropItem == nullptr)
	{
		m_textPrompt.Enqueue(L"[오류] : [" + dropItems[randNum] + L"] 해당 아이템이 존재하지 않습니다.");
		m_isCombatEnded = true;
		return;
	}

	ItemInstance dropItemInstance(*dropItem);
	if (player.GetInventory().AddItem(move(dropItemInstance)) == false)
	{
		m_textPrompt.Enqueue(L"시스템 : 인벤토리가 가득 차 아이템을 획득하지 못했습니다.");
		return;
	}

	m_textPrompt.Enqueue(L"시스템 : 전리품으로 [" + dropItem->GetItemName() + L"] 를 획득했습니다.");

	m_isCombatEnded = true;
	delete dropItem;
}
