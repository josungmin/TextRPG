#include "PlayerCharacter.h"
#include "../GameInstance.h"
#include "../Item/EquipableItem.h"

PlayerCharacter::PlayerCharacter(const wstring& characterName, const wstring& description)
	: CombatCharacter(characterName, description)
{
	m_statContainer.stats[EStatType::HP].baseValue = 50;
	m_statContainer.stats[EStatType::AttackPower].baseValue = 10;
	m_statContainer.stats[EStatType::Defence].baseValue = 5;
	m_statContainer.stats[EStatType::Agility].baseValue = 7;

	m_currentHP = m_statContainer.GetStatValue(EStatType::HP);
}
