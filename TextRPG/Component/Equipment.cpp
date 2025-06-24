#include "Equipment.h"
#include "../GameInstance.h"
#include "../Stat/StatDataType.h"
#include "../Item/EquipableItem.h"

Equipment::Equipment()
{
	m_equipedItemList.reserve(static_cast<uint8>(EquipableItem::EEquipType::Max));
}

Equipment::~Equipment()
{
	m_equipedItemList.clear();
}

const bool Equipment::IsEquiped(EquipableItem::EEquipType equipType) const
{
	vector<ItemInstance>::const_iterator it = m_equipedItemList.begin();
	for (it; it != m_equipedItemList.end(); ++it)
	{
		if (equipType == it->Get<EquipableItem>()->GetEquipType())
		{
			return true;
		}
	}

	return false;
}

const bool Equipment::EquipItem(ItemInstance itemInstance, StatContainer& ownerStatContainer)
{
	m_equipedItemList.push_back(move(itemInstance));
	return true;
}

ItemInstance Equipment::UnequipItem(EquipableItem::EEquipType type, StatContainer& ownerStatContainer)
{
	vector<ItemInstance>::iterator it = m_equipedItemList.begin();
	for (it; it != m_equipedItemList.end(); ++it)
	{
		if (type == it->Get<EquipableItem>()->GetEquipType())
		{
			break;
		}
	}

	ItemInstance unequipped = std::move(*it);
	m_equipedItemList.erase(it);
	return unequipped;
}

const EquipableItem* Equipment::GetEquipedItem(EquipableItem::EEquipType equipType) const
{
	vector<ItemInstance>::const_iterator it = m_equipedItemList.begin();
	for (it; it != m_equipedItemList.end(); ++it)
	{
		if (equipType == it->Get<EquipableItem>()->GetEquipType())
		{
			return it->Get<EquipableItem>();
		}
	}

	return nullptr;
}
