#pragma once
#include "CombatCharacter.h"
#include "../Stat/StatDataType.h"
#include "../Component/Equipment.h"

class PlayerCharacter : public CombatCharacter
{
public:
	PlayerCharacter(const wstring& characterName, const wstring& description);
	
public:
	inline Experience& GetExperience() { return experience; }
	inline Gold& GetGold() { return gold; }
	inline Equipment& GetEquipment() { return equipment; }

protected:
	Experience experience;
	Gold gold;
	Equipment equipment;
};