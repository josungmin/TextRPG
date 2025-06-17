#include "Inventory.h"
#include "../GameInstance.h"

Inventory::Inventory()
	:m_inventorySize(5)
{
	m_itemList.reserve(m_inventorySize);
}

Inventory::~Inventory()
{
	for (Item* item : m_itemList)
	{
		delete item;
	}
}

const bool Inventory::AddItem(const wstring& itemName, const uint8 amount)
{
	const Item* newItem = GameInstance::Instance().GetItemTable().CreateItem(itemName);
	if (AddItem(newItem, amount) == false)
	{
		delete newItem;
		return false;
	}

	delete newItem;
	return true;
}

const bool Inventory::AddItem(const Item* item, const uint8 amount)
{
	if (item == nullptr)
	{
		return false;
	}

	if (item->GetType() == EquipableItem::EItemType::Equip)
	{
		if (IsFull())
		{
			return false;
		}

		m_itemList.push_back(item->Clone());
		return true;
	}

	for (uint8 i = 0; i < m_itemList.size(); i++)
	{
		Item* targetItem = m_itemList[i];
		if (targetItem->GetItemName() != item->GetItemName())
		{
			continue;
		}

		if (targetItem->IsFull())
		{
			continue;
		}

		if (targetItem->GetRemainCount() < amount)
		{
			return false;
		}

		return targetItem->AddItem(amount);
	}

	if (IsFull())
	{
		return false;
	}

	m_itemList.push_back(item->Clone());
	return true;
}

const bool Inventory::RemoveItem(const wstring& itemName, const uint8 amount)
{
	vector<Item*>::iterator it = std::find_if(
		m_itemList.begin(), 
		m_itemList.end(), 
		[=](Item* item)
		{ 
			return item->GetItemName() == itemName; 
		});

	if (it == m_itemList.end())
	{
		return false;
	}

	Item* targetItem = *it;
	if (targetItem->GetCount() == amount)
	{
		m_itemList.erase(it);
		return true;
	}
	
	return targetItem->RemoveItem(amount);
}