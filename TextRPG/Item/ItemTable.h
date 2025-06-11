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
	Item* CreateItem(const wstring& id) const;
	inline const std::unordered_map<std::wstring, Item*>& GetItemMap() const { return m_itemMap; }

private:
	void Load(); //TODO: �׽�Ʈ �ڵ�

private:
	std::unordered_map<wstring, Item*> m_itemMap;
};
