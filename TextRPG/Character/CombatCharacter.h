#pragma once
#include "Character.h"
#include "../Stat/StatDataType.h"

//class StatContainer;

class CombatCharacter : public Character
{
public:
	CombatCharacter(const wstring& characterName, const wstring& description);

public:
	virtual void TakeDamage(uint16_t damage);
	virtual void HealHp(uint16_t amount);

public:
	inline const uint16_t GetCurrentHP() const { return m_currentHP; }
	inline const bool GetIsDead() const { return m_IsDead; }
	inline StatContainer& GetStats() { return m_statContainer; }

protected:
	virtual uint16_t CalculateDamage(uint16_t damage);

protected:
	uint16_t m_currentHP = 0;
	bool m_IsDead = false;

	StatContainer m_statContainer;
};