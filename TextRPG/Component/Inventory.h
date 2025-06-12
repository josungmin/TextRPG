#pragma once
#include <string>
#include <vector>
#include "../MyType.h"

using namespace std;

class Item;

class Inventory
{
public:
	Inventory() = default;
	~Inventory();

public:
	bool AddItem(Item* item);
	bool RemoveItem(const wstring& itemName);

	inline vector<Item*>& GetItems() { return m_items; }

private:
	vector<Item*> m_items;
};