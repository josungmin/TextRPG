#pragma once
#include <string>
#include <memory>

enum class EItemType : uint8_t
{
	Equip,
};

class Item
{
public:

	virtual ~Item() {}
	virtual std::shared_ptr<Item> Clone() const = 0;

public:
	inline void SetType(EItemType itemType) { this->itemType = itemType; }
	inline void SetMaxCount(uint8_t maxCount) { this->maxCount = maxCount; }

	inline bool AddItem(int num = 1)
	{
		if (count + num > maxCount)
		{
			return false;
		}

		count += num;
		return true;
	}

	inline bool RemoveItem(int num = 1)
	{
		if (count <= 0 || count - num < 0)
		{
			return false;
		}

		count -= num;

		if (count < 0)
		{
			count = 0;
		}

		return true;
	}

public:
	inline const EItemType GetType() const { return itemType; }
	inline const int GetCount() const { return count; }
	inline const int GetMaxCount() const { return maxCount; }
	inline const std::wstring& GetItemName() const { return itemName; }
	inline const std::wstring& GetDescription() const { return description; }
	inline const int GetBuyPrice() const { return buyPrice; }
	inline const int GetSellPrice() const { return sellPrice; }

private:
	EItemType itemType;
	uint8_t maxCount = 99;

protected:
	uint8_t count = 1;
	std::wstring itemName{ L"Item Name" };
	std::wstring description{ L"Item description" };
	uint8_t buyPrice = 0;
	uint8_t sellPrice = 0;
};