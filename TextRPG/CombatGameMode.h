#pragma once

class CombatCharacter;

class CombatGameMode
{
public:
	CombatGameMode() = default;
	~CombatGameMode() = default;

public:
	void ProcessCombat(CombatCharacter& enemy);

private:
	void PlayerTurn(CombatCharacter& enemy);
	void EnemyTurn(CombatCharacter& enemy);
};