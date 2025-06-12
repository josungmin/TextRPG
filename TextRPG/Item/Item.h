#pragma once
#include <string>
#include "../MyType.h"

using namespace std;

enum class EItemType : uint8
{
	None,
	Equip,
	Other,
};

class Item
{
public:
	Item(const EItemType itemType, const wstring& itemName, const wstring& description, const uint8 buyPrice, const uint8 sellPrice)
		:m_itemType(itemType), m_itemName(itemName), m_description(description), m_buyPrice(buyPrice), m_sellPrice(sellPrice)
	{

	}
	~Item() = default;

	virtual Item* Clone() const
	{
		return new Item(*this);
	}

public:
	inline void SetMaxCount(uint8 maxCount) { m_maxCount = maxCount; }

	inline bool AddItem(uint8 num = 1)
	{
		if (m_count + num > m_maxCount)
		{
			return false;
		}

		m_count += num;
		return true;
	}

	inline bool RemoveItem(uint8 num = 1)
	{
		if (m_count <= 0 || m_count - num < 0)
		{
			return false;
		}

		m_count -= num;

		if (m_count < 0)
		{
			m_count = 0;
		}

		return true;
	}

public:
	inline const EItemType GetType() const { return m_itemType; }
	inline const uint8 GetCount() const { return m_count; }
	inline const uint8 GetMaxCount() const { return m_maxCount; }
	inline const wstring& GetItemName() const { return m_itemName; }
	inline const wstring& GetDescription() const { return m_description; }
	inline const uint8 GetBuyPrice() const { return m_buyPrice; }
	inline const uint8 GetSellPrice() const { return m_sellPrice; }

private:
	uint8 m_maxCount = 99;

protected:
	uint8 m_count = 1;

	const EItemType m_itemType = EItemType::None;
	const wstring m_itemName{ L"Item Name" };
	const wstring m_description{ L"Item description" };
	const uint8 m_buyPrice = 0;
	const uint8 m_sellPrice = 0;
};