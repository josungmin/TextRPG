#pragma once
#include "CombatCharacter.h"
#include "../Stat/StatDataType.h"
#include "../Component/Equipment.h"
#include "../Component/Inventory.h"

class PlayerCharacter : public CombatCharacter
{
public:
	PlayerCharacter(const wstring& characterName, const wstring& description);
	virtual ~PlayerCharacter() = default;
	
public:
	inline Experience& GetExperience() { return m_experience; }
	inline Gold& GetGold() { return m_gold; }
	inline Equipment& GetEquipment() { return m_equipment; }
	inline Inventory& GetInventory() { return m_inventory; }

protected:
	Experience m_experience;
	Gold m_gold;
	Equipment m_equipment;
	Inventory m_inventory;
};