#include "CombatGameMode.h"
#include <memory>

#include "GameInstance.h"
#include "Character/PlayerCharacter.h"
#include "Scene/TitleScene.h"

void CombatGameMode::ProcessCombat(CombatCharacter& enemy)
{
	PlayerCharacter player = GameInstance::Instance().GetPlayer();

	if (player.GetStats().GetStatValue(EStatType::Agility) < enemy.GetStats().GetStatValue(EStatType::Agility))
	{
		EnemyTurn(enemy);

		if (player.GetIsDead() == false)
		{
			PlayerTurn(enemy);
		}

	}
	else
	{
		PlayerTurn(enemy);

		if (enemy.GetIsDead() == false)
		{
			EnemyTurn(enemy);
		}
	}
}

void CombatGameMode::PlayerTurn(CombatCharacter& enemy)
{
	PlayerCharacter player = GameInstance::Instance().GetPlayer();

	enemy.TakeDamage(player.GetStats().GetStatValue(EStatType::AttackPower));
}

void CombatGameMode::EnemyTurn(CombatCharacter& enemy)
{
	PlayerCharacter player = GameInstance::Instance().GetPlayer();

	player.TakeDamage(enemy.GetStats().GetStatValue(EStatType::AttackPower));
}
