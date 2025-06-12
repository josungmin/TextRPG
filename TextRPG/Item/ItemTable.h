#pragma once
#include <string>
#include <unordered_map>
#include "Item.h"

class Item;

using namespace std;

class ItemTable
{
public:
	ItemTable();
	~ItemTable();

public:
	Item* CreateItem(const wstring& name) const;
	const Item* GetItem(const wstring& name) const;
	inline const unordered_map<wstring, Item*>& GetItemMap() const { return m_itemMap; }

private:
	void Load();

private:
	unordered_map<wstring, Item*> m_itemMap;
};
