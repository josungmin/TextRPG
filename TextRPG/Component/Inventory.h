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

private:
	// TODO: 자료형 변경 고민중
	vector<Item*> m_items;
};