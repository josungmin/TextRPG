#pragma once
#include <algorithm>
#include "Item.h"

class ItemInstance
{
public:
	ItemInstance()
		: m_pItem(nullptr) { }

	ItemInstance(const Item& item)
		: m_pItem(item.Clone()) { }

	ItemInstance(ItemInstance&& rhs) noexcept
		:ItemInstance()
	{
		swap(this->m_pItem, rhs.m_pItem);
	}

	ItemInstance& operator=(ItemInstance&& rhs) noexcept
	{
		ItemInstance temp = ItemInstance(move(rhs));
		swap(this->m_pItem, temp.m_pItem);
		return *this;
	}

	virtual ~ItemInstance()
	{
		delete m_pItem;
	}

	ItemInstance(const ItemInstance&) = delete;
	ItemInstance& operator=(const ItemInstance&) = delete;

public:
	template<typename T>
	inline T* Get() const { return dynamic_cast<T*>(m_pItem); }
	inline Item* Get() const { return m_pItem; }
	inline const bool IsValid() const { return m_pItem != nullptr; }

private:
	Item* m_pItem = nullptr;
};