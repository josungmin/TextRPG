#include "Inventory.h"
#include "../GameInstance.h"

Inventory::Inventory()
	:m_inventorySize(5)
{
	m_itemList.reserve(m_inventorySize);
}

Inventory::~Inventory()
{
	m_itemList.clear();
}

const bool Inventory::AddItem(ItemInstance itemInstance, const uint8 amount)
{
	if (IsFull() == true)
	{
		return false;
	}

	if (itemInstance.Get()->GetType() == EquipableItem::EItemType::Equip)
	{
		itemInstance.Get()->AddItem(amount);
		m_itemList.push_back(move(itemInstance));
		return true;
	}

	for (ItemInstance& inst : m_itemList)
	{
		if (inst.Get()->GetItemName() == itemInstance.Get()->GetItemName())
		{
			if (inst.Get()->IsFull())
			{
				continue;
			}

			if (inst.Get()->GetRemainCount() < amount)
			{
				return false;
			}

			return inst.Get()->AddItem(amount);
		}
	}

	itemInstance.Get()->AddItem(amount);
	m_itemList.push_back(move(itemInstance));
	return true;
}

ItemInstance Inventory::RemoveItem(const wstring& itemName, const uint8 amount)
{
	vector<ItemInstance>::iterator it = std::find_if(
		m_itemList.begin(),
		m_itemList.end(),
		[&](const ItemInstance& inst)
		{
			return inst.Get()->GetItemName() == itemName;
		});

	if (it == m_itemList.end())
	{
		return ItemInstance();
	}

	Item* targetItem = it->Get();
	if (targetItem->GetCount() < amount)
	{
		return ItemInstance();
	}
	
	if (targetItem->GetCount() == amount)
	{
		ItemInstance removedItemInstance(move(*it));
		m_itemList.erase(it);
		return removedItemInstance;
	}

	targetItem->RemoveItem(amount);

	ItemInstance removedItemInstance(*(it->Get()));
	removedItemInstance.Get()->AddItem(amount);
	return removedItemInstance;
}
