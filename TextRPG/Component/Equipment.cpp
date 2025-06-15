#include "Equipment.h"

Equipment::~Equipment()
{
    if (m_weapon != nullptr)
    {
        delete m_weapon;
    }
    
    if (m_armor != nullptr)
    {
        delete m_armor;
    }
}

const bool Equipment::Equip(const EquipableItem* item, StatContainer& statContainer)
{
    if (!item)
    {
        return false;
    }

    EquipableItem* equipItem = static_cast<EquipableItem*>(item->Clone());
    const ModifierContainer& modifierContainer = equipItem->GetModifierContainer();

    switch (item->GetEquipType())
    {
        case EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
                delete m_weapon;
            }

            m_weapon = equipItem;
            statContainer.AddModifierContainer(modifierContainer);
            return true;

            return true;
        }         
        case EEquipType::Armor:
        {
            if (m_armor)
            {
                statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
                delete m_armor;
            }
            
            m_armor = equipItem;
            statContainer.AddModifierContainer(modifierContainer);
            return true;
        }
        default:
        {
            delete equipItem;
            return false;
        }      
    }
}

const EquipableItem* Equipment::Unequip(EEquipType type, StatContainer& statContainer)
{
    EquipableItem* unequipItem = nullptr;

    switch (type)
    {
        case EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
                unequipItem = m_weapon;
                m_weapon = nullptr;
                return unequipItem;
            }
            break;
        }
        case EEquipType::Armor:
        {
            if (m_armor)
            {
                statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
                unequipItem = m_armor;
                m_armor = nullptr;
                return unequipItem;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return nullptr;
}

const bool Equipment::IsEquiped(EEquipType equipType) const
{
    switch (equipType)
    {
        case EEquipType::NONE:
        {
            break;
        }        
        case EEquipType::Weapon:
        {
            return m_weapon != nullptr;
            break;
        }
        case EEquipType::Armor:
        {
            return m_armor != nullptr;
            break;
        }
        default:
        {
            break;
        }
    }

    return false;
}
