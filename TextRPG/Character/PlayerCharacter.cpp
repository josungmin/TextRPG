#include "PlayerCharacter.h"
#include "../GameInstance.h"
#include "../Item/EquipableItem.h"

PlayerCharacter::PlayerCharacter(const wstring& characterName, const wstring& description)
	: CombatCharacter(characterName, description)
{
	statContainer.stats[EStatType::HP].baseValue = 50;
	statContainer.stats[EStatType::AttackPower].baseValue = 5;
	statContainer.stats[EStatType::Defence].baseValue = 5;
	statContainer.stats[EStatType::Agility].baseValue = 5;

	currentHP = statContainer.GetStatValue(EStatType::HP);
}
