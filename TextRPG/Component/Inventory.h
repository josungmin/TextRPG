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
	const bool AddItem(ItemInstance itemInstance, const uint8 amount = 1);
	ItemInstance RemoveItem(const wstring& itemName, const uint8 amount = 1);

public:
	inline const bool IsFull() const { return m_itemList.size() >= m_inventorySize; }
	inline const vector<ItemInstance>& GetItemList() const { return m_itemList; }

private:
	const uint8 m_inventorySize = 5;
	vector<ItemInstance> m_itemList;
};