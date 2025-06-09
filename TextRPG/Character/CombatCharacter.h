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
	inline StatContainer& GetStats() { return statContainer; }
	inline const uint16_t GetCurrentHP() const { return currentHP; }
	inline const bool GetIsDead() const { return bIsDead; }

protected:
	virtual uint16_t CalculateDamage(uint16_t damage);

protected:
	StatContainer statContainer;

	uint16_t currentHP = 0;
	bool bIsDead = false;
};