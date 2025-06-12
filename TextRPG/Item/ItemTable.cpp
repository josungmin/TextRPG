#include "ItemTable.h"
#include "Item.h"
#include "EquipableItem.h"

ItemTable::ItemTable()
{
	Load();
}

ItemTable::~ItemTable()
{
	std::unordered_map<std::wstring, Item*>::iterator it;
	for (it = m_itemMap.begin(); it != m_itemMap.end(); ++it)
	{
		delete it->second;
	}
}

void ItemTable::Load()
{
	// Sword item 1
	EquipableItem* sword = new EquipableItem(
		EEquipType::Weapon, 
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

	m_itemMap[sword->GetItemName()] = sword; //insert()?
	
	// Sword Item 2
	EquipableItem* lightSword = new EquipableItem(
		EEquipType::Weapon, 
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

	m_itemMap[lightSword->GetItemName()] = lightSword; //insert()

	// Sword item 3
	EquipableItem* bronzeSword = new EquipableItem(
		EEquipType::Weapon, 
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

	m_itemMap[bronzeSword->GetItemName()] = bronzeSword;


	// Amor item
	EquipableItem* amor = new EquipableItem(
		EEquipType::Armor, 
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

	m_itemMap[amor->GetItemName()] = amor;


	// Other items
	Item* goblenBone = new Item(
		EItemType::Other, 
		L"����� ��",
		L"��� óġ �� ���� Ȯ���� ȹ���� �� �ִ�.", 
		0, 
		2
	);

	m_itemMap[goblenBone->GetItemName()] = goblenBone;
}

Item* ItemTable::CreateItem(const wstring& name) const
{
	std::unordered_map<std::wstring, Item*>::const_iterator it = m_itemMap.find(name);
	if (it != m_itemMap.end())
	{
		return it->second->Clone();
	}
		
	return nullptr;
}

const Item* ItemTable::GetItem(const wstring& name) const
{
	std::unordered_map<std::wstring, Item*>::const_iterator it = m_itemMap.find(name);
	if (it != m_itemMap.end())
	{
		return it->second;
	}
		
	return nullptr;
}
