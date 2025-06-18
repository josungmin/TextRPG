#include "Item.h"

Item::Item(const EItemType itemType, const wstring& itemName, const wstring& description, const uint8 buyPrice, const uint8 sellPrice)
	:m_itemType(itemType), m_itemName(itemName), m_description(description), m_buyPrice(buyPrice), m_sellPrice(sellPrice)
{

}

Item::~Item()
{

}

bool Item::AddItem(uint8 num)
{
	if (m_count + num > m_maxCount)
	{
		return false;
	}

	m_count += num;
	return true;
}

bool Item::RemoveItem(uint8 num)
{
	if (m_count <= 0 || m_count < num)
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
