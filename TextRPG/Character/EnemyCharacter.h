#pragma once
#include "CombatCharacter.h"
#include "../Stat/StatDataType.h"

class EnemyCharacter : public CombatCharacter
{
public:
	EnemyCharacter(const wstring& characterName, const wstring& description, const StatContainer& statContainer);
};