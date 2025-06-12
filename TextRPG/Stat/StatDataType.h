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
		auto it = stats.find(statType);
		if (it == stats.end())
		{
			return 0;
		}

		if (!it->second.bIsChanged)
		{
			return it->second.finalValue;
		}

		uint16 calculated = CalculateStatValue(statType);
		it->second.finalValue = calculated;
		it->second.bIsChanged = false;

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
		auto it = stats.find(statType);
		if (it == stats.end())
		{
			return 0;
		}

		uint16 result = it->second.baseValue + it->second.bonusValue;

		for (const auto& pair : modifierContainers)
		{
			const auto& container = pair.second;

			for (const auto& modifier : container.modifiers)
			{
				if (modifier.targetStatType != statType)
				{
					continue;
				}

				switch (modifier.modifierType)
				{
				case EModifierType::Add:
				{
					result += modifier.value;
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
		for (const auto& mod : container.modifiers)
		{
			auto it = stats.find(mod.targetStatType);
			if (it != stats.end())
			{
				it->second.bIsChanged = true;
			}
		}
	}
};

struct Experience
{
	int8 m_currentExp = 0;
	int8 m_level = 1;

	explicit Experience(int8_t level) : m_level(level), m_currentExp(0) {}

	int8 GetRequiredExpForNextLevel() const
	{
		return 3 + (m_level - 1) * 5;
	}

	bool AddExperience(const int8 amount)
	{
		m_currentExp += amount;
		bool leveledUp = false;

		while (m_currentExp >= GetRequiredExpForNextLevel())
		{
			m_currentExp -= GetRequiredExpForNextLevel();
			m_level++;
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
	uint16 m_amount = 10000;

	explicit Gold(uint16_t initialAmount) : m_amount(initialAmount) {}

	void AddGold(const uint16 amount)
	{
		uint32 total = (m_amount + amount);

		if (total > UINT8_MAX)
		{
			m_amount = UINT8_MAX;
		}

		m_amount = (uint16)total;
	}

	bool RemoveGold(const uint16 amount)
	{
		if (m_amount < amount)
		{
			return false;
		}

		m_amount -= amount;
		return true;
	}
};