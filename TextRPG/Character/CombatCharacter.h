#pragma once
#include "Character.h"
#include "../MyType.h"
#include "../Stat/StatDataType.h"

class CombatCharacter : public Character
{
public:
	CombatCharacter(const wstring& characterName, const wstring& description);

public:
	virtual void TakeDamage(const uint16 damage);
	virtual void HealHp(const uint16 amount);

public:
	inline const uint16 GetCurrentHP() const { return m_currentHP; }
	inline const bool GetIsDead() const { return m_IsDead; }
	inline StatContainer& GetStats() { return m_statContainer; }

protected:
	virtual const uint16 CalculateDamage(uint16 damage);

protected:
	uint16 m_currentHP = 0;
	bool m_IsDead = false;

	StatContainer m_statContainer;
};