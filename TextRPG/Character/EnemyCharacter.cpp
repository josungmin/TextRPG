#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(const wstring& characterName, const wstring& description, const StatContainer& statContainer)
	: CombatCharacter(characterName, description)
{
	this->m_statContainer = statContainer;
	m_currentHP = this->m_statContainer.GetStatValue(EStatType::HP);
}