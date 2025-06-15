#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(const wstring& characterName, const wstring& description, const int8 dropExp, const uint16 m_dropGold, const StatContainer& statContainer)
	: CombatCharacter(characterName, description), m_dropExp(dropExp), m_dropGold(m_dropGold)
{
	m_statContainer = statContainer;
	m_currentHP = m_statContainer.GetStatValue(EStatType::HP);

	m_dropItems.reserve(3);
	m_dropItems.push_back(L"최하급 검");
	m_dropItems.push_back(L"하급 검");
	m_dropItems.push_back(L"고블린의 뼈");
}