#include "ItemTable.h"
#include "Item.h"
#include "EquipableItem.h"

void ItemTable::Load()
{
	// Sword item 1
	EquipableItem* sword = new EquipableItem(
		EEquipType::WEAPON, 
		EItemType::Equip, 
		L"최하급 검", 
		L"언제 부러질지 모르는 최하급 무기이다.",
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
		L"하급 검", 
		L"한두번 정도는 더 사용할 수 있을듯 한 하급 무기이다.", 
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
		L"일반 검", 
		L"좋지도 나쁘지도 않은 일반적인 무기이다.", 
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
		L"최하급 갑옷",
		L"공격이 닿으면 부서질것 같은 최하급 갑옷이다.", 
		10, 
		5
	);

	ModifierContainer amordMod;
	amordMod.id = amor->GetItemName();
	amordMod.modifiers.push_back({ EStatType::Defence, EModifierType::Add, 1 });
	amor->SetModifierContainer(amordMod);

	itemDatas[amor->GetItemName()] = amor;


	// Other items
	Item* goblenBone = new Item(EItemType::Other, L"고블린의 뼈", L"고블린 처치 시 일정 확률로 획득할 수 있다.", 0, 2);
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
