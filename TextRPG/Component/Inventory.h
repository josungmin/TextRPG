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
	// TODO: �ڷ��� ���� �����
	vector<Item*> m_items;
};