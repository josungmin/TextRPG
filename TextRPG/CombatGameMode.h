#pragma once
#include "MyType.h"

class CombatCharacter;
class EnemyCharacter;
class TextPrompt;

enum class ECombatState : uint8
{
	CombatStart,
	CombatEnd,
	PlayerAction,
	EnemyAction,
	PlayerInput,
};

class CombatGameMode
{
public:
	CombatGameMode(TextPrompt& textPrompt);
	~CombatGameMode();

public:
	void ProcessCombat();
	void SetEnemy(EnemyCharacter& Enemy);

private:
	void CombatStart();
	void PlayerAction();
	void EnemyAction();
	void CombatEnd();

private:
	TextPrompt& m_textPrompt;
	EnemyCharacter* m_enemy;

	ECombatState currentCombatState;
	bool m_isCombat = false;
};