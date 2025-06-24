#pragma once
#include <memory>
#include "../Item/EquipableItem.h"
#include "../Item/ItemInstance.h"

struct StatContainer;

class Equipment
{
public:
    Equipment();
    virtual ~Equipment();

public:
    const bool EquipItem(ItemInstance itemInstance, StatContainer& ownerStatContainer);
    ItemInstance UnequipItem(EquipableItem::EEquipType type, StatContainer& ownerStatContainer);

public:
    const EquipableItem* GetEquipedItem(EquipableItem::EEquipType equipType) const;
    const bool IsEquiped(EquipableItem::EEquipType equipType) const;

private:
    vector<ItemInstance> m_equipedItemList;
};


