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
	friend class ItemTable;

public:
	Item(const EItemType itemType, const wstring& itemName, const wstring& description, const uint8 buyPrice, const uint8 sellPrice);
	virtual ~Item();
	Item& operator=(const Item& rhs) = delete;

protected:
	Item(const Item& rhs) = default;


public://private:
	virtual Item* Clone() const
	{
		return new Item(*this);
	}


public:
	bool AddItem(uint8 num = 1);
	bool RemoveItem(uint8 num = 1);

	inline void SetMaxCount(const uint8 maxCount) { m_maxCount = maxCount; }
	inline const bool IsFull() const { return m_count == m_maxCount; }

	inline const EItemType GetType() const { return m_itemType; }
	inline const uint8 GetCount() const { return m_count; }
	inline const uint8 GetRemainCount() const { return m_maxCount - m_count; }
	inline const uint8 GetMaxCount() const { return m_maxCount; }
	inline const wstring& GetItemName() const { return m_itemName; }
	inline const wstring& GetDescription() const { return m_description; }
	inline const uint8 GetBuyPrice() const { return m_buyPrice; }
	inline const uint8 GetSellPrice() const { return m_sellPrice; }

	//TODO: 임시코드
	inline const wstring GetItemNameNoneSpace() 
	{
		wstring noneSpaceName = m_itemName;
		noneSpaceName.erase(remove(noneSpaceName.begin(), noneSpaceName.end(), ' '), noneSpaceName.end());

		return noneSpaceName;
	}

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