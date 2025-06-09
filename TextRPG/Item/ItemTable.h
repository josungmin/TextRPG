#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "Item.h"

class ItemTable
{
public:
	ItemTable() { Load(); }
	~ItemTable() { }

public:
	std::shared_ptr<Item> CreateItem(const std::wstring& id) const;
	inline const std::unordered_map<std::wstring, std::shared_ptr<Item>>& GetItemMap() const { return itemMap; }

private:
	void Load();

private:
	std::unordered_map<std::wstring, std::shared_ptr<Item>> itemMap;
};
