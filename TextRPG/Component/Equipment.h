#pragma once
#include <memory>
#include "../Item/EquipableItem.h"
#include "../Stat/StatDataType.h"
#include "../Item/ItemInstance.h"

class Equipment
{
public:
    Equipment();
    virtual ~Equipment();

public:
    const bool Equip(const EquipableItem* item, StatContainer& ownerStatContainer);
    const bool Unequip(EquipableItem::EEquipType type, StatContainer& ownerStatContainer);
    const bool IsEquiped(EquipableItem::EEquipType equipType) const;

    inline const EquipableItem* GetWeapon() const { return m_weapon; }
    inline const EquipableItem* GetArmor() const { return m_armor; }

    const bool EquipItemInstance(const ItemInstance& itemInstance, StatContainer& ownerStatContainer);
    const ItemInstance& UnequipItemInstance(EquipableItem::EEquipType type, StatContainer& ownerStatContainer);

    const EquipableItem* GetEquipedItem(EquipableItem::EEquipType equipType) const;

private:
    EquipableItem* m_weapon = nullptr;
    EquipableItem* m_armor = nullptr;

private:
    vector<ItemInstance> equipedItemList;
};


