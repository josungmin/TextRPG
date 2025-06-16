#pragma once
#include "Item.h"
#include "../Stat/StatDataType.h"

enum class EEquipType : uint8_t
{
	Weapon = 0,
	Armor = 1,
};

class EquipableItem : public Item
{
public:
	EquipableItem(const EEquipType equipType, const EItemType itemType, const std::wstring& itemName, const std::wstring& description, const uint8_t buyPrice, const uint8_t sellPrice);

public:
	virtual Item* Clone() const override 
	{ 
		return new EquipableItem(*this); 
	}

public:
	inline const EEquipType GetEquipType() const { return m_equipType; }
	inline void SetEquipType(EEquipType type) { m_equipType = type; }
	inline const ModifierContainer& GetModifierContainer() const { return m_modifierContainer; }
	inline void SetModifierContainer(const ModifierContainer& container) { m_modifierContainer = container; }

private:
	EEquipType m_equipType;
	ModifierContainer m_modifierContainer;
};