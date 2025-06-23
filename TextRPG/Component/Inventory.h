#pragma once
#include <vector>
#include "../MyType.h"
#include "../Item/ItemInstance.h"

using namespace std;

class Inventory
{
public:
	Inventory();
	virtual ~Inventory();

public:
	const bool AddItem(const Item& item, const uint8 amount = 1);
	const bool RemoveItem(const wstring& itemName, const uint8 amount = 1);
	inline const bool IsFull() const { return m_itemList.size() >= m_inventorySize; }

public:
	inline const vector<ItemInstance>& GetItemList() const { return m_itemList; }

private:
	const uint8 m_inventorySize = 5;
	vector<ItemInstance> m_itemList;
};