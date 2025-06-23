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
    const bool EquipItemInstance(const ItemInstance& itemInstance, StatContainer& ownerStatContainer);
    ItemInstance UnequipItemInstance(EquipableItem::EEquipType type, StatContainer& ownerStatContainer);

    const EquipableItem* GetEquipedItem(EquipableItem::EEquipType equipType) const;
    const bool IsEquiped(EquipableItem::EEquipType equipType) const;

private:
    vector<ItemInstance> equipedItemList;
};


