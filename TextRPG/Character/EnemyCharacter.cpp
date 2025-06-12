#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(const wstring& characterName, const wstring& description, const StatContainer& statContainer)
	: CombatCharacter(characterName, description)
{
	m_statContainer = statContainer;
	m_currentHP = m_statContainer.GetStatValue(EStatType::HP);
}