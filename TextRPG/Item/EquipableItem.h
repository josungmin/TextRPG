#pragma once
#include "Item.h"
#include "../Stat/StatDataType.h"

class EquipableItem : public Item
{
public:
	enum class EEquipType : uint8
	{
		Weapon,
		Armor,
		Max,
	};

public:
	EquipableItem(const EEquipType equipType, const EItemType itemType, const std::wstring& itemName, const std::wstring& description, const uint8_t buyPrice, const uint8_t sellPrice);
	virtual ~EquipableItem() = default;

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

protected:
	EEquipType m_equipType;
	ModifierContainer m_modifierContainer;
};