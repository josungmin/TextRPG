#pragma once
#include <memory>
#include "../Item/EquipableItem.h"
#include "../Stat/StatDataType.h"

class Equipment
{
public:
    ~Equipment();

public:
    bool Equip(EquipableItem* item, StatContainer& ownerStatContainer);
    bool Unequip(EEquipType type, StatContainer& ownerStatContainer);

    inline EquipableItem* GetWeapon() const { return m_weapon; }
    inline EquipableItem* GetArmor() const { return m_armor; }

private:
    EquipableItem* m_weapon = nullptr;
    EquipableItem* m_armor = nullptr;
};