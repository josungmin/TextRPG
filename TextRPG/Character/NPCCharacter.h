#pragma once
#include "Character.h"

class NPCCharacter : public Character
{
public:
	NPCCharacter(const wstring& characterName, const wstring& description)
		:Character(characterName, description) { }

public:
	virtual void Interact() = 0;
};