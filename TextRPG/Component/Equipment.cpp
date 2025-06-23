#include "Equipment.h"
#include "../GameInstance.h"
#include "../Stat/StatDataType.h"
#include "../Item/EquipableItem.h"

Equipment::Equipment()
{
	equipedItemList.reserve(static_cast<uint8>(EquipableItem::EEquipType::Max));
}

Equipment::~Equipment()
{
	equipedItemList.clear();
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

ItemInstance Equipment::UnequipItemInstance(EquipableItem::EEquipType type, StatContainer& ownerStatContainer)
{
	vector<ItemInstance>::iterator it = equipedItemList.begin();
	for (it; it != equipedItemList.end(); ++it)
	{
		if (type == it->Get<EquipableItem>()->GetEquipType())
		{
			break;
		}
	}

	ItemInstance unequipped = std::move(*it);
	equipedItemList.erase(it);
	return unequipped;
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
