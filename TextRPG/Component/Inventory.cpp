#include "Inventory.h"
#include "../Item/Item.h"

Inventory::Inventory()
	:m_size(5)
{
	m_items.reserve(m_size);
}

Inventory::~Inventory()
{
	for (Item* item : m_items)
	{
		delete item;
	}
}

bool Inventory::AddItem(Item* item)
{
	if (item == nullptr || m_items.size() == m_size)
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
		m_items.erase(it);
		return true;
	}

	return false;
}
