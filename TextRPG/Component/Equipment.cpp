#include "Equipment.h"

Equipment::~Equipment()
{
    delete m_weapon;
    delete m_armor;
}

bool Equipment::Equip(EquipableItem* item, StatContainer& statContainer)
{
    if (!item)
    {
        return false;
    }

    const ModifierContainer& modifierContainer = item->GetModifierContainer();

    switch (item->GetEquipType())
    {
        case EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
            }

            m_weapon = item;
            statContainer.AddModifierContainer(modifierContainer);

            return true;
        }         
        case EEquipType::Armor:
        {
            if (m_armor)
            {
                statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
            }
            
            m_armor = item;
            statContainer.AddModifierContainer(modifierContainer);

            return true;
        }
        default:
        {
            return false;
        }      
    }
}

bool Equipment::Unequip(EEquipType type, StatContainer& statContainer)
{

    switch (type)
    {
        case EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
                m_weapon = nullptr;
                return true;
            }
            break;
        }   
        case EEquipType::Armor:
        {
            if (m_armor)
            {
                statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
                m_armor = nullptr;
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
