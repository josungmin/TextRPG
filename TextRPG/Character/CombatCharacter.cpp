#include "CombatCharacter.h"
#include <algorithm>
#include <iostream>

CombatCharacter::CombatCharacter(const wstring& characterName, const wstring& description)
	:Character(characterName, description)
{
	
}

void CombatCharacter::TakeDamage(const uint16 damage)
{
	m_currentHP -= CalculateDamage(damage);
	if (m_currentHP <= 0)
	{
		m_IsDead = true;
	}
}

void CombatCharacter::HealHp(const uint16 amount)
{
	const uint16 maxHP = m_statContainer.GetStatValue(EStatType::HP);
	const uint16 result = std::min((m_currentHP + amount), (int32)maxHP);
	m_currentHP = result;
}

const uint16 CombatCharacter::CalculateDamage(uint16 damage)
{
	const uint16 defence = m_statContainer.GetStatValue(EStatType::Defence);
	const uint16 result = damage - defence;

	return result < 0 ? 0 : result;
}