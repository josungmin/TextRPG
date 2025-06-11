#include "EquipableItem.h"

EquipableItem::EquipableItem(const EEquipType equipType, const EItemType itemType, const std::wstring& itemName, const std::wstring& description, const uint8_t buyPrice, const uint8_t sellPrice)
	:Item(itemType, itemName, description, buyPrice, sellPrice), m_equipType(equipType)
{
	
}