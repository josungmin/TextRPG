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

const bool Inventory::AddItem(const Item& item, const uint8 amount)
{
	if (IsFull() == true)
	{
		return false;
	}

	if (item.GetType() == EquipableItem::EItemType::Equip)
	{
		m_itemList.emplace_back(item);
		return true;
	}

	for (ItemInstance& inst : m_itemList)
	{
		if (inst.Get()->GetItemName() == item.GetItemName())
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

	m_itemList.emplace_back(item);
	return true;
}

const bool Inventory::RemoveItem(const wstring& itemName, const uint8 amount)
{
	auto it = std::find_if(
		m_itemList.begin(),
		m_itemList.end(),
		[&](const ItemInstance& inst) {
			return inst.Get()->GetItemName() == itemName;
		});

	if (it == m_itemList.end())
	{
		return false;
	}		

	Item* targetItem = it->Get();
	if (targetItem->GetCount() < amount)
	{
		return false;
	}	

	if (targetItem->GetCount() == amount)
	{
		m_itemList.erase(it);
		return true;
	}

	return targetItem->RemoveItem(amount);
}

