#pragma once
#include <memory>
#include "../Item/EquipableItem.h"
#include "../Stat/StatDataType.h"

class Equipment
{
public:
    ~Equipment();

public:
    const bool Equip(const EquipableItem* item, StatContainer& ownerStatContainer);
    const EquipableItem* Unequip(EEquipType type, StatContainer& ownerStatContainer);
    const bool IsEquiped(EEquipType equipType) const;

    inline const EquipableItem* GetWeapon() const { return m_weapon; }
    inline const EquipableItem* GetArmor() const { return m_armor; }

private:
    EquipableItem* m_weapon = nullptr;
    EquipableItem* m_armor = nullptr;
};