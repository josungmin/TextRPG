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
	const uint32_t total = static_cast<uint32_t>(currentHP + amount);
	const uint32_t maxHP = static_cast<uint32_t>(statContainer.GetStatValue(EStatType::HP));

	if (total > maxHP)
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