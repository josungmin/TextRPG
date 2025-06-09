#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(const wstring& characterName, const wstring& description, const StatContainer& statContainer)
	: CombatCharacter(characterName, description)
{
	this->statContainer = statContainer;
	currentHP = this->statContainer.GetStatValue(EStatType::HP);
}