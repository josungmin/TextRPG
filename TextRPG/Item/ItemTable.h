#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <map>

class Item;

using namespace std;

class ItemTable
{
public:
	ItemTable();
	~ItemTable();

public:
	Item* CreateItem(const wstring& name) const;
	inline const unordered_map<wstring, Item*>& GetItemMap() const { return m_itemMap; }

private:
	void Load(); //TODO: 테스트 코드

private:
	unordered_map<wstring, Item*> m_itemMap;
};
