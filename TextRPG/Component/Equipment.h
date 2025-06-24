#pragma once
#include <array>
#include "../Item/EquipableItem.h"
#include "../Item/ItemInstance.h"

struct StatContainer;

class Equipment
{
public:
    Equipment() = default;
    virtual ~Equipment() = default;

public:
    const bool EquipItem(ItemInstance itemInstance, StatContainer& ownerStatContainer);
    ItemInstance UnequipItem(EquipableItem::EEquipType equipType, StatContainer& ownerStatContainer);

public:
    const EquipableItem* GetEquipedItem(EquipableItem::EEquipType equipType) const;
    const bool IsEquiped(EquipableItem::EEquipType equipType) const;

private:
    array<ItemInstance, static_cast<size_t>(EquipableItem::EEquipType::Max)> m_equipedItemList;
};


