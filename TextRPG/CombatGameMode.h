#pragma once
#include "MyType.h"
#include <string>

using namespace std;

class CombatCharacter;
class EnemyCharacter;
class TextPrompt;

enum class ECombatState : uint8
{
	CombatStart,
	CombatEnd,
	PlayerAction,
	EnemyAction,
	WaitForPlayerInput,
};

class CombatGameMode
{
public:
	CombatGameMode(TextPrompt& textPrompt);
	virtual ~CombatGameMode();

public:
	void ProcessCombat();
	void SetEnemy(EnemyCharacter& Enemy);
	void SetPlayerCommand(const wstring& command);
	const bool IsCombatEnd() const { return m_isCombatEnded; }

private:
	void CombatStart();
	void PlayerAction();
	void EnemyAction();
	void CombatEnd();

private:
	TextPrompt& m_textPrompt;
	EnemyCharacter* m_enemy;

	ECombatState m_currentCombatState;
	wstring m_command;
	bool m_isCombatEnded = false;
};