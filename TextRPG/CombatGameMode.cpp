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
	m_textPrompt.Enqueue(L"�ý��� : ������ �����մϴ�.");

	const uint16 playerAgility = GameInstance::GetInstance().GetPlayer().GetStats().GetStatValue(EStatType::Agility);
	const uint16 enemyAgility = m_enemy->GetStats().GetStatValue(EStatType::Agility);

	if (playerAgility >= enemyAgility)
	{
		m_textPrompt.Enqueue(L"�ý��� : �÷��̾ �����մϴ�. � �ൿ�� �Ͻðڽ��ϱ�?");
		m_textPrompt.Enqueue(L"�ý��� : 1.���� 2.ȸ��");
		m_currentCombatState = ECombatState::WaitForPlayerInput;
		return;
	}
	else
	{
		m_textPrompt.Enqueue(L"�ý��� : �� ĳ���Ͱ� �����մϴ�.");
		m_currentCombatState = ECombatState::EnemyAction;
		return;
	}
}

void CombatGameMode::PlayerAction()
{
	PlayerCharacter& player = GameInstance::GetInstance().GetPlayer();

	if (m_command == L"1" || m_command == L"����" || m_command == L"1����" || m_command == L"1.����")
	{
		const uint16 damage = player.GetStats().GetStatValue(EStatType::AttackPower);
		m_enemy->TakeDamage(damage);

		m_textPrompt.Enqueue(L"�÷��̾� : [" + m_enemy->GetName() + L"]" + L"���� " + to_wstring(damage) + L" ���ظ� �������ϴ�. ���� �� HP " + std::to_wstring(m_enemy->GetCurrentHP()));
	}
	else if (m_command == L"2" || m_command == L"ȸ��" || m_command == L"2ȸ��" || m_command == L"2.ȸ��")
	{
		const uint16 amount = 10;
		player.HealHp(amount);
		m_textPrompt.Enqueue(L"�÷��̾� : HP�� " + std::to_wstring(amount) + L" ȸ���߽��ϴ�.");
	}
	else
	{
		m_textPrompt.Enqueue(L"�ý��� : �߸��� ����Դϴ�. �ٽ� �����ϼ���.");
		m_currentCombatState = ECombatState::WaitForPlayerInput;
		return;
	}

	m_command.clear();

	if (m_enemy->GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : ���� óġ�߽��ϴ�!");
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

	m_textPrompt.Enqueue(m_enemy->GetName() + L" : " + L"[" + player.GetName() + L"]" + L"���� " + to_wstring(damage) + L" ���ظ� �������ϴ�. ���� �÷��̾� HP " + std::to_wstring(player.GetCurrentHP()));

	if (player.GetIsDead() == true)
	{
		m_textPrompt.Enqueue(L"�ý��� : ����� ���������ϴ�...");
		m_currentCombatState = ECombatState::CombatEnd;
		return;
	}
	else
	{
		m_textPrompt.Enqueue(L"�ý��� : �÷��̾ �����մϴ�. � �ൿ�� �Ͻðڽ��ϱ�?");
		m_textPrompt.Enqueue(L"�ý��� : 1.���� 2.ȸ��");
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
	m_textPrompt.Enqueue(L"�ý��� : " + std::to_wstring(dropExp) + L" ����ġ�� ȹ���߽��ϴ�.");

	const uint16 dropGold = m_enemy->GetDropGold();
	player.GetGold().AddGold(dropGold);
	m_textPrompt.Enqueue(L"�ý��� : " + std::to_wstring(dropGold) + L" ��带 ȹ���߽��ϴ�.");

	const vector<wstring>& dropItems = m_enemy->GetDropItems();
	const uint64 randNum = rand() % dropItems.size();

	const Item* dropItem = GameInstance::GetInstance().GetItemTable().CreateItem(dropItems[randNum]);
	if (dropItem == nullptr)
	{
		m_textPrompt.Enqueue(L"[����] : [" + dropItems[randNum] + L"] �ش� �������� �������� �ʽ��ϴ�.");
		m_isCombatEnded = true;
		return;
	}

	ItemInstance dropItemInstance(*dropItem);
	if (player.GetInventory().AddItem(move(dropItemInstance)) == false)
	{
		m_textPrompt.Enqueue(L"�ý��� : �κ��丮�� ���� �� �������� ȹ������ ���߽��ϴ�.");
		return;
	}

	m_textPrompt.Enqueue(L"�ý��� : ����ǰ���� [" + dropItem->GetItemName() + L"] �� ȹ���߽��ϴ�.");

	m_isCombatEnded = true;
	delete dropItem;
}
