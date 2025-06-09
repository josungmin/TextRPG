#pragma once
#include "Item.h"
#include "../Stat/StatDataType.h"

enum class EquipType : uint8_t
{
	NONE,
	WEAPON,
	ARMOR,
};

class EquipableItem : public Item
{
public:
	EquipableItem(const std::wstring& itemName, const std::wstring& description, uint8_t buyPrice, uint8_t sellPrice);
	virtual ~EquipableItem() override;

	std::shared_ptr<Item> Clone() const override
	{
		return std::make_shared<EquipableItem>(*this);
	}

	inline EquipType GetEquipType() const { return equipType; }
	inline void SetEquipType(EquipType type) { equipType = type; }
	inline const ModifierContainer& GetModifierContainer() const { return modifierContainer; }
	inline void SetModifierContainer(const ModifierContainer& container) { modifierContainer = container; }

private:
	EquipType equipType = EquipType::NONE;
	ModifierContainer modifierContainer;
};