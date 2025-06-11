#include "Inventory.h"
#include "../Item/Item.h"

Inventory::~Inventory()
{
	for (Item* item : m_items)
	{
		delete item;
	}
}

bool Inventory::AddItem(Item* item)
{
	if (!item)
	{
		return false;
	}

	m_items.push_back(item);
	return true;
}

bool Inventory::RemoveItem(const wstring& itemName)
{
	vector<Item*>::iterator it = std::find_if(m_items.begin(), m_items.end(), [=](Item* item)
	{ 
		return item->GetItemName() == itemName; 
	});

	if (it != m_items.end())
	{
		delete* it;
		m_items.erase(it);
		return true;
	}

	return false;
}
