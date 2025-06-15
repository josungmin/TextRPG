#pragma once
#include <string>
#include <vector>
#include "../MyType.h"
#include "../Item/Item.h"

using namespace std;

class Item;

class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	const bool AddItem(const Item* item, const uint8 amount = 1);
	const bool RemoveItem(const wstring& itemName, const uint8 amount = 1);
	inline const bool IsFull() const { return m_itemList.size() == m_inventorySize; }

public:
	inline vector<Item*>& GetItemList() { return m_itemList; }

private:
	const bool FindPred(Item& item1, Item& item2) const
	{
		return item1.GetItemName() == item2.GetItemName();
	}

private:
	const uint8 m_inventorySize = 5;
	vector<Item*> m_itemList;
};