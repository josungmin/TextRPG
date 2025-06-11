#include "ItemTable.h"
#include "Item.h"
#include "EquipableItem.h"

void ItemTable::Load()
{
	// Sword item 1
	EquipableItem* sword = new EquipableItem(
		EEquipType::WEAPON, 
		EItemType::Equip, 
		L"���ϱ� ��", 
		L"���� �η����� �𸣴� ���ϱ� �����̴�.",
		10,
		5
	);

	ModifierContainer swordMod;
	swordMod.id = sword->GetItemName();
	swordMod.modifiers.push_back({ EStatType::AttackPower, EModifierType::Add, 1 });
	sword->SetModifierContainer(swordMod);

	itemDatas[sword->GetItemName()] = sword; //insert()?
	
	// Sword Item 2
	EquipableItem* lightSword = new EquipableItem(
		EEquipType::WEAPON, 
		EItemType::Equip, 
		L"�ϱ� ��", 
		L"�ѵι� ������ �� ����� �� ������ �� �ϱ� �����̴�.", 
		20, 
		10
	);

	ModifierContainer lightSwordMod;
	lightSwordMod.id = lightSword->GetItemName();
	lightSwordMod.modifiers.push_back({ EStatType::AttackPower, EModifierType::Add, 1 });
	lightSwordMod.modifiers.push_back({ EStatType::Agility, EModifierType::Add, 1 });
	lightSword->SetModifierContainer(lightSwordMod);

	itemDatas[lightSword->GetItemName()] = lightSword; //insert()?

	// Sword item 3
	EquipableItem* bronzeSword = new EquipableItem(
		EEquipType::WEAPON, 
		EItemType::Equip, 
		L"�Ϲ� ��", 
		L"������ �������� ���� �Ϲ����� �����̴�.", 
		30, 
		15
	);

	ModifierContainer bronzeSwordMod;
	bronzeSwordMod.id = bronzeSword->GetItemName();
	bronzeSwordMod.modifiers.push_back({ EStatType::AttackPower, EModifierType::Add, 2 });
	bronzeSwordMod.modifiers.push_back({ EStatType::Agility, EModifierType::Add, 1 });
	bronzeSword->SetModifierContainer(bronzeSwordMod);

	itemDatas[lightSword->GetItemName()] = lightSword;



	// Amor item
	EquipableItem* amor = new EquipableItem(
		EEquipType::ARMOR, 
		EItemType::Equip, 
		L"���ϱ� ����",
		L"������ ������ �μ����� ���� ���ϱ� �����̴�.", 
		10, 
		5
	);

	ModifierContainer amordMod;
	amordMod.id = amor->GetItemName();
	amordMod.modifiers.push_back({ EStatType::Defence, EModifierType::Add, 1 });
	amor->SetModifierContainer(amordMod);

	itemDatas[amor->GetItemName()] = amor;


	// Other items
	Item* goblenBone = new Item(EItemType::Other, L"����� ��", L"��� óġ �� ���� Ȯ���� ȹ���� �� �ִ�.", 0, 2);
	itemDatas[goblenBone->GetItemName()] = goblenBone;
}

std::shared_ptr<Item> ItemTable::CreateItem(const wstring& id) const
{
    auto it = itemMap.find(id);
    if (it == itemMap.end())
    {
        return nullptr;
    }

    return it->second->Clone();
}
