#include "CombatCharacter.h"

CombatCharacter::CombatCharacter(const wstring& characterName, const wstring& description)
	:Character(characterName, description)
{
	
}

void CombatCharacter::TakeDamage(uint16_t damage)
{
	m_currentHP -= CalculateDamage(damage);
	if (m_currentHP <= 0)
	{
		m_IsDead = true;
	}
}

void CombatCharacter::HealHp(uint16_t amount)
{
	const uint32_t total = static_cast<uint32_t>(m_currentHP + amount);
	const uint32_t maxHP = static_cast<uint32_t>(m_statContainer.GetStatValue(EStatType::HP));

	if (total > maxHP)
	{
		m_currentHP = maxHP;
	}
}

uint16_t CombatCharacter::CalculateDamage(uint16_t damage)
{
	const uint16_t defence = m_statContainer.GetStatValue(EStatType::Defence);
	uint16_t result = damage - defence;

	return result < 0 ? 0 : result;
}