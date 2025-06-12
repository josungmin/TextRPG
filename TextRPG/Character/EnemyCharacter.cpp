#include "EnemyCharacter.h"

EnemyCharacter::EnemyCharacter(const wstring& characterName, const wstring& description, int8 dropExp, uint16 m_dropGold, const StatContainer& statContainer)
	: CombatCharacter(characterName, description), m_dropExp(dropExp), m_dropGold(m_dropGold)
{
	m_statContainer = statContainer;
	m_currentHP = m_statContainer.GetStatValue(EStatType::HP);

	dropItems.reserve(3);
	dropItems.push_back(L"���ϱ� ��");
	dropItems.push_back(L"�ϱ� ��");
	dropItems.push_back(L"����� ��");
}