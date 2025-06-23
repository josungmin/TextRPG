#include "Equipment.h"
#include "../GameInstance.h"
#include "../Item/EquipableItem.h"

Equipment::Equipment()
{
	equipedItemList.reserve(static_cast<uint8>(EquipableItem::EEquipType::Max));
}

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

const bool Equipment::Equip(const EquipableItem* item, StatContainer& ownerStatContainer)
{
	EquipableItem* equipItem = dynamic_cast<EquipableItem*>(item->Clone());
	const ModifierContainer& modifierContainer = equipItem->GetModifierContainer();

	switch (item->GetEquipType())
	{
		case EquipableItem::EEquipType::Weapon:
		{
			if (m_weapon)
			{
				ownerStatContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
				delete m_weapon;
			}

			m_weapon = equipItem;
			ownerStatContainer.AddModifierContainer(modifierContainer);
			return true;
		}
		case EquipableItem::EEquipType::Armor:
		{
			if (m_armor)
			{
				ownerStatContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
				delete m_armor;
			}

			m_armor = equipItem;
			ownerStatContainer.AddModifierContainer(modifierContainer);
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
			if (m_weapon != nullptr)
			{
				statContainer.RemoveModifierContainer(m_weapon->GetModifierContainer().id);
				delete m_weapon;
				m_weapon = nullptr;
				return true;
			}
			break;
		}
		case EquipableItem::EEquipType::Armor:
		{
			if (m_armor != nullptr)
			{
				statContainer.RemoveModifierContainer(m_armor->GetModifierContainer().id);
				delete m_armor;
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
	vector<ItemInstance>::const_iterator it = equipedItemList.begin();
	for (it; it != equipedItemList.end(); ++it)
	{
		if (equipType == it->Get<EquipableItem>()->GetEquipType())
		{
			return true;
		}
	}

	return false;
}

const bool Equipment::EquipItemInstance(const ItemInstance& itemInstance, StatContainer& ownerStatContainer)
{
	ItemInstance equipItemInstance(*itemInstance.Get());
	equipedItemList.push_back(std::move(equipItemInstance));
	return true;
}

const ItemInstance& Equipment::UnequipItemInstance(EquipableItem::EEquipType type, StatContainer& ownerStatContainer)
{
	vector<ItemInstance>::iterator it = equipedItemList.begin();
	for (it; it != equipedItemList.end(); ++it)
	{
		if (type == it->Get<EquipableItem>()->GetEquipType())
		{
			break;
		}
	}

	return ItemInstance(*it->Get());
}

const EquipableItem* Equipment::GetEquipedItem(EquipableItem::EEquipType equipType) const
{
	vector<ItemInstance>::const_iterator it = equipedItemList.begin();
	for (it; it != equipedItemList.end(); ++it)
	{
		if (equipType == it->Get<EquipableItem>()->GetEquipType())
		{
			return it->Get<EquipableItem>();
		}
	}

	return nullptr;
}
