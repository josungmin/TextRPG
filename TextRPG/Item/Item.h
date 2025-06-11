#pragma once
#include <string>
#include <memory>

using namespace std;

enum class EItemType : uint8_t
{
	None,
	Equip,
	Other,
};

class Item
{
public:
	Item(const EItemType itemType, const std::wstring& itemName, const std::wstring& description, const uint8_t buyPrice, const uint8_t sellPrice)
		:m_itemType(itemType), m_itemName(itemName), m_description(description), m_buyPrice(buyPrice), m_sellPrice(sellPrice)
	{

	}
	~Item() = default;

	virtual std::shared_ptr<Item> Clone() const
	{
		return std::make_shared<Item>(*this);
	}

public:
	inline void SetMaxCount(uint8_t maxCount) { m_maxCount = maxCount; }

	inline bool AddItem(int num = 1)
	{
		if (m_count + num > m_maxCount)
		{
			return false;
		}

		m_count += num;
		return true;
	}

	inline bool RemoveItem(int num = 1)
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
	inline const int GetCount() const { return m_count; }
	inline const int GetMaxCount() const { return m_maxCount; }
	inline const std::wstring& GetItemName() const { return m_itemName; }
	inline const std::wstring& GetDescription() const { return m_description; }
	inline const int GetBuyPrice() const { return m_buyPrice; }
	inline const int GetSellPrice() const { return m_sellPrice; }

private:
	uint8_t m_maxCount = 99;

protected:
	uint8_t m_count = 1;

	const EItemType m_itemType = EItemType::None;
	const std::wstring m_itemName{ L"Item Name" };
	const std::wstring m_description{ L"Item description" };
	const uint8_t m_buyPrice = 0;
	const uint8_t m_sellPrice = 0;
};