#include "EquipableItem.h"

EquipableItem::EquipableItem(const std::wstring& itemName, const std::wstring& description, uint8_t buyPrice, uint8_t sellPrice)
{
	this->itemName = itemName;
	this->description = description;
	this->buyPrice = buyPrice;
	this->sellPrice = sellPrice;

	SetMaxCount(1);
}

EquipableItem::~EquipableItem()
{

}
