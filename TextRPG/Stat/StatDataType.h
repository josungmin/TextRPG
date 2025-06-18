#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../MyType.h"

using namespace std;

enum class EStatType : uint8
{
	HP,
	AttackPower,
	Defence,
	Agility
};

enum class EModifierType : uint8
{
	Add,
};

struct Modifier
{
	EStatType targetStatType;
	EModifierType modifierType;
	uint8 value = 0;
};

struct ModifierContainer
{
	wstring id;
	vector<Modifier> modifiers;
};

struct Stat
{
	uint8 baseValue = 0;
	uint8 bonusValue = 0;
	uint16 finalValue = 0;
	bool bIsChanged = true;
};

struct StatContainer
{
	unordered_map<EStatType, Stat> stats;
	unordered_map<wstring, ModifierContainer> modifierContainers;

	uint16 GetStatValue(EStatType statType)
	{
		unordered_map<EStatType, Stat>::iterator stats_it = stats.find(statType);
		if (stats_it == stats.end())
		{
			return 0;
		}

		if (!stats_it->second.bIsChanged)
		{
			return stats_it->second.finalValue;
		}

		uint16 calculated = CalculateStatValue(statType);
		stats_it->second.finalValue = calculated;
		stats_it->second.bIsChanged = false;

		return calculated;
	}

	void AddModifierContainer(const ModifierContainer& container)
	{
		modifierContainers[container.id] = container;
		SetChangeStats(container);
	}

	void RemoveModifierContainer(const wstring& id)
	{
		auto it = modifierContainers.find(id);
		if (it != modifierContainers.end())
		{
			SetChangeStats(it->second);
			modifierContainers.erase(it);
		}
	}

private:
	uint16 CalculateStatValue(EStatType statType) const
	{
		unordered_map<EStatType, Stat>::const_iterator stats_it = stats.find(statType);
		if (stats_it == stats.end())
		{
			return 0;
		}

		uint16 result = stats_it->second.baseValue + stats_it->second.bonusValue;

		for (unordered_map<wstring, ModifierContainer>::const_iterator modifierContainer_it = modifierContainers.begin(); modifierContainer_it != modifierContainers.end(); modifierContainer_it++)
		{
			const ModifierContainer& container = (*modifierContainer_it).second;

			for (vector<Modifier>::const_iterator modifier_it = container.modifiers.begin(); modifier_it != container.modifiers.end(); modifier_it++)
			{
				if ((*modifier_it).targetStatType != statType)
				{
					continue;
				}

				switch ((*modifier_it).modifierType)
				{
					case EModifierType::Add:
					{
						result += (*modifier_it).value;
						break;
					}
					default:
					{
						break;
					}
				}
			}
		}

		return result;
	}

	void SetChangeStats(const ModifierContainer& container)
	{
		for (vector<Modifier>::const_iterator modifier_it = container.modifiers.begin(); modifier_it != container.modifiers.end(); modifier_it++)
		{
			unordered_map<EStatType, Stat>::iterator stat = stats.find((*modifier_it).targetStatType);
			if (stat != stats.end())
			{
				stat->second.bIsChanged = true;
			}
		}
	}
};

struct Experience
{
	uint8 currentExp = 0;
	uint8 level = 1;

	Experience() : level(1), currentExp(0) {}
	explicit Experience(int8 level) : level(level), currentExp(0) {}

	uint8 GetRequiredExpForNextLevel() const
	{
		return 3 + (level - 1) * 5;
	}

	bool AddExperience(const uint8 amount)
	{
		currentExp += amount;
		bool leveledUp = false;

		while (currentExp >= GetRequiredExpForNextLevel())
		{
			currentExp -= GetRequiredExpForNextLevel();
			level++;
			leveledUp = true;
		}

		return leveledUp;
	}
};

template <uint8 MaxLevel>
struct ExperienceTable
{
	array<uint8, MaxLevel> requiredExpPerLevel;

	uint8 GetRequiredExp(const uint8 level) const
	{
		if (level <= 0 || static_cast<uint8>(level - 1) >= requiredExpPerLevel.size())
		{
			return UINT8_MAX;
		}

		return requiredExpPerLevel[level - 1];
	}
};

struct Gold
{
	uint16 amount = 10000;

	Gold() : amount(10000) {}
	explicit Gold(uint16 initialAmount) : amount(initialAmount) {}

	void AddGold(const uint16 addAmount)
	{
		uint32 total = (amount + addAmount);

		if (total > UINT8_MAX)
		{
			amount = UINT8_MAX;
		}

		amount = (uint16)total;
	}

	bool RemoveGold(const uint16 removeAmount)
	{
		if (amount < removeAmount)
		{
			return false;
		}

		amount -= removeAmount;
		return true;
	}
};