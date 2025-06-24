#include "Equipment.h"
#include "../GameInstance.h"
#include "../Stat/StatDataType.h"
#include "../Item/EquipableItem.h"

Equipment::Equipment()
{
	
}

Equipment::~Equipment()
{
	
}

const bool Equipment::IsEquiped(EquipableItem::EEquipType equipType) const
{
	uint8 index = static_cast<uint8>(equipType);
	if (index < 0 || static_cast<uint8>(EquipableItem::EEquipType::Max) < index)
	{
		return false;
	}

	return m_equipedItemListTemp[index].IsValid();
}

const bool Equipment::EquipItem(ItemInstance itemInstance, StatContainer& ownerStatContainer)
{
	if (itemInstance.IsValid() == false)
	{
		return false;
	}

	uint8 index = static_cast<uint8>(itemInstance.Get<EquipableItem>()->GetEquipType());
	if (m_equipedItemListTemp[index].IsValid() == true)
	{
		return false;
	}

	//const EquipableItem* selectedItem = m_equipedItemListTemp[index].Get<EquipableItem>();
	//ownerStatContainer.AddModifierContainer(selectedItem->GetModifierContainer());

	m_equipedItemListTemp[index] = move(itemInstance);
	return true;
}

ItemInstance Equipment::UnequipItem(EquipableItem::EEquipType equipType, StatContainer& ownerStatContainer)
{
	uint8 index = static_cast<uint8>(equipType);
	if (index < 0 || static_cast<uint8>(EquipableItem::EEquipType::Max) <= index)
	{
		return ItemInstance();
	}

	if (m_equipedItemListTemp[index].IsValid() == false)
	{
		return ItemInstance();
	}

	//const EquipableItem* selectedItem = m_equipedItemListTemp[index].Get<EquipableItem>();
	//ownerStatContainer.RemoveModifierContainer(selectedItem->GetModifierContainer().id);

	return move(m_equipedItemListTemp[index]);
}

const EquipableItem* Equipment::GetEquipedItem(EquipableItem::EEquipType equipType) const
{
	uint8 index = static_cast<uint8>(equipType);
	if (index < 0 || static_cast<uint8>(EquipableItem::EEquipType::Max) <= index)
	{
		return nullptr;
	}

	return m_equipedItemListTemp[index].Get<EquipableItem>();
}
