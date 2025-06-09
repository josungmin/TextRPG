#pragma once
#include <string>
#include <vector>
#include <unordered_map>

enum class EStatType : uint8_t
{
	HP,
	AttackPower,
	Defence,
	Agility
};

enum class EModifierType : uint8_t
{
	Add,
};

struct Modifier
{
	EStatType targetStatType;
	EModifierType modifierType;
	uint8_t value = 0;
};

struct ModifierContainer
{
	std::wstring id;
	std::vector<Modifier> modifiers;

	bool operator==(const ModifierContainer& other) const
	{
		return id == other.id;
	}
};

struct Stat
{
	uint8_t baseValue = 0;
	uint8_t bonusValue = 0;
	uint16_t finalValue = 0;
	bool bIsChanged = true;
};

struct StatContainer
{
	std::unordered_map<EStatType, Stat> stats;
	std::unordered_map<std::wstring, ModifierContainer> modifierContainers;

	uint16_t GetStatValue(EStatType statType)
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

		uint16_t calculated = CalculateStatValue(statType);
		it->second.finalValue = calculated;
		it->second.bIsChanged = false;

		return calculated;
	}

	void AddModifierContainer(const ModifierContainer& container)
	{
		modifierContainers[container.id] = container;
		SetChangeStats(container);
	}

	void RemoveModifierContainer(const std::wstring& id)
	{
		auto it = modifierContainers.find(id);
		if (it != modifierContainers.end())
		{
			SetChangeStats(it->second);
			modifierContainers.erase(it);
		}
	}

private:
	uint16_t CalculateStatValue(EStatType statType) const
	{
		auto it = stats.find(statType);
		if (it == stats.end())
		{
			return 0;
		}

		uint16_t result = it->second.baseValue + it->second.bonusValue;

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
					result += modifier.value;
					break;

				default:
					break;
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
	int8_t currentExp = 0;
	int8_t level = 1;

	int8_t GetRequiredExpForNextLevel() const
	{
		return 3 + (level - 1) * 5;
	}

	bool AddExperience(const int8_t amount)
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

template <uint8_t MaxLevel>
struct ExperienceTable
{
	std::array<uint8_t, MaxLevel> requiredExpPerLevel;

	uint8_t GetRequiredExp(const uint8_t level) const
	{
		if (level <= 0 || static_cast<uint8_t>(level - 1) >= requiredExpPerLevel.size())
		{
			return UINT8_MAX;
		}
			
		return requiredExpPerLevel[level - 1];
	}
};

struct Gold
{
	uint16_t amount = 10000;
	
	void AddGold(const uint16_t amount)
	{
		uint32_t total = (this->amount + amount);

		if (total > UINT8_MAX)
		{
			this->amount = UINT8_MAX;
		}

		this->amount = (uint16_t)total;
	}

	bool RemoveGold(const uint16_t amount)
	{
		if (this->amount < amount)
		{
			return false;
		}

		this->amount -= amount;
		return true;
	}
};