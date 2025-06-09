#include "ItemTable.h"
#include "Item.h"
#include "EquipableItem.h"

void ItemTable::Load()
{
	auto sword = std::make_shared<EquipableItem>(L"Sword", L"basic sword", 10, 5);
	sword->SetType(EItemType::Equip);
	sword->SetEquipType(EquipType::WEAPON);

	ModifierContainer swordMod;
	swordMod.id = L"sword";
	swordMod.modifiers.push_back({ EStatType::AttackPower, EModifierType::Add, 5 });

	sword->SetModifierContainer(swordMod);
	itemMap[L"Sword"] = sword;

	auto armor = std::make_shared<EquipableItem>(L"Armor", L"light armor", 8, 4);
	armor->SetType(EItemType::Equip);
	armor->SetEquipType(EquipType::ARMOR);

	ModifierContainer armorMod;
	armorMod.id = L"armor";
	armorMod.modifiers.push_back({ EStatType::Defence, EModifierType::Add, 3 });

	armor->SetModifierContainer(armorMod);
	itemMap[L"Armor"] = armor;
}

std::shared_ptr<Item> ItemTable::CreateItem(const std::wstring& id) const
{
    auto it = itemMap.find(id);
    if (it == itemMap.end())
    {
        return nullptr;
    }

    return it->second->Clone();
}
