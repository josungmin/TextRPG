#include "CombatCharacter.h"
//TODO: 임시코드
#include <windows.h>

CombatCharacter::CombatCharacter(const wstring& characterName, const wstring& description)
	:Character(characterName, description)
{
	
}

void CombatCharacter::TakeDamage(uint16 damage)
{
	m_currentHP -= CalculateDamage(damage);
	if (m_currentHP <= 0)
	{
		m_IsDead = true;
		MessageBox(NULL, TEXT("Combat Character is Dead"), TEXT("Text"), MB_OK);
	}
}

void CombatCharacter::HealHp(uint16 amount)
{
	const uint32_t total = static_cast<uint32_t>(m_currentHP + amount);
	const uint32_t maxHP = static_cast<uint32_t>(m_statContainer.GetStatValue(EStatType::HP));

	if (total > maxHP)
	{
		m_currentHP = maxHP;
	}
}

uint16 CombatCharacter::CalculateDamage(uint16 damage)
{
	const uint16 defence = m_statContainer.GetStatValue(EStatType::Defence);
	uint16 result = damage - defence;

	return result < 0 ? 0 : result;
}