#include "Equipment.h"

bool Equipment::Equip(std::shared_ptr<EquipableItem> item, StatContainer& statContainer)
{
    if (!item)
    {
        return false;
    }

    const ModifierContainer& modifierContainer = item->GetModifierContainer();

    switch (item->GetEquipType())
    {
    case EquipType::WEAPON:
    {
        if (weapon)
        {
            statContainer.RemoveModifierContainer(weapon->GetModifierContainer().id);
        }

        weapon = item;
        statContainer.AddModifierContainer(modifierContainer);

        return true;
    }         
    case EquipType::ARMOR:
    {
        if (armor)
        {
            statContainer.RemoveModifierContainer(armor->GetModifierContainer().id);
        }
            
        armor = item;
        statContainer.AddModifierContainer(modifierContainer);

        return true;
    }
    default:
    {
        return false;
    }      
    }
}

bool Equipment::Unequip(EquipType type, StatContainer& statContainer)
{
    switch (type)
    {
    case EquipType::WEAPON:
    {
        if (weapon)
        {
            statContainer.RemoveModifierContainer(weapon->GetModifierContainer().id);
            weapon = nullptr;
            return true;
        }

        break;
    }   
    case EquipType::ARMOR:
    {
        if (armor)
        {
            statContainer.RemoveModifierContainer(armor->GetModifierContainer().id);
            armor = nullptr;
            return true;
        }

        break;
    }     
    default:
    {
        break;
    }   
    }

    return false;
}
