#include "CombatCharacter.h"

CombatCharacter::CombatCharacter(const wstring& characterName, const wstring& description)
	:Character(characterName, description)
{
	
}

void CombatCharacter::TakeDamage(uint16_t damage)
{
	currentHP -= CalculateDamage(damage);
	if (currentHP <= 0)
	{
		bIsDead = true;
	}
}

void CombatCharacter::HealHp(uint16_t amount)
{
	currentHP += amount;

	const uint16_t maxHP = statContainer.GetStatValue(EStatType::HP);
	if (currentHP >= maxHP)
	{
		currentHP = maxHP;
	}
}

uint16_t CombatCharacter::CalculateDamage(uint16_t damage)
{
	const uint16_t defence = statContainer.GetStatValue(EStatType::Defence);
	uint16_t result = damage - defence;

	return result < 0 ? 0 : result;
}