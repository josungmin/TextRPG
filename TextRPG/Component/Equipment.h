#pragma once
#include <memory>
#include "../Item/EquipableItem.h"
#include "../Stat/StatDataType.h"

class Equipment
{
public:
    bool Equip(std::shared_ptr<EquipableItem> item, StatContainer& ownerStatContainer);
    bool Unequip(EEquipType type, StatContainer& ownerStatContainer);

    inline std::shared_ptr<EquipableItem> GetWeapon() const { return weapon; }
    inline std::shared_ptr<EquipableItem> GetArmor() const { return armor; }

private:
    std::shared_ptr<EquipableItem> weapon = nullptr;
    std::shared_ptr<EquipableItem> armor = nullptr;
};