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
    case EquipableItem::EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
                delete m_weapon;
            }

            m_weapon = equipItem;
            statContainer.AddModifierContainer(modifierContainer);
            return true;
        }         
    case EquipableItem::EEquipType::Armor:
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

const bool Equipment::Unequip(EquipableItem::EEquipType type, StatContainer& statContainer)
{
    switch (type)
    {
    case EquipableItem::EEquipType::Weapon:
        {
            if (m_weapon)
            {
                statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
                //delete m_weapon;
                m_weapon = nullptr;
                return true;
            }
            break;
        }
    case EquipableItem::EEquipType::Armor:
        {
            if (m_armor)
            {
                statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
                //delete m_armor;
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

const bool Equipment::IsEquiped(EquipableItem::EEquipType equipType) const
{
    switch (equipType)
    {
        case EquipableItem::EEquipType::Weapon:
        {
            return m_weapon != nullptr;
            break;
        }
        case EquipableItem::EEquipType::Armor:
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
