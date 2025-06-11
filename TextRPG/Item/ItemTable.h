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
	ItemTable() { Load(); }
	~ItemTable() { }

public:
	//public Item FindItem(wstring itemName);

	shared_ptr<Item> CreateItem(const wstring& id) const;
	inline const unordered_map<wstring, shared_ptr<Item>>& GetItemMap() const { return itemMap; }

private:
	void Load(); //TODO: 테스트 코드

private:
	std::unordered_map<wstring, shared_ptr<Item>> itemMap;

	std::map<const wstring, Item*> itemDatas;
};
