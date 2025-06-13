#pragma once
#include <string>
#include <vector>
#include "../MyType.h"

using namespace std;

class Item;

class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	bool AddItem(Item* item);
	bool RemoveItem(const wstring& itemName);

	inline vector<Item*>& GetItems() { return m_items; }

private:
	const uint8 m_size = 5;
	vector<Item*> m_items;
};