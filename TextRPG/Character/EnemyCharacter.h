#pragma once
#include <string>
#include "CombatCharacter.h"
#include "../Stat/StatDataType.h"

class EnemyCharacter : public CombatCharacter
{
public:
	EnemyCharacter(const wstring& characterName, const wstring& description, int8 dropExp, uint16 m_dropGold, const StatContainer& statContainer);

public:
	inline const int8 GetDropExp() const { return m_dropExp; }
	inline const uint16 GetDropGold() const { return m_dropGold; }
	inline const vector<wstring>& GetDropItems() const { return dropItems; }

private:
	int8 m_dropExp = 10;
	uint16 m_dropGold = 100;
	vector<wstring> dropItems;
};