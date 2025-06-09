#pragma once
#include <string>
#include <vector>

using namespace std;

class Character
{
public:
	Character(const wstring& characterName, const wstring& description)
		:characterName(characterName), description(description) { }
	virtual ~Character() = default;

public:
	inline const wstring& GetName() const { return characterName; }
	inline const wstring& GetDescription() const { return description; }

protected:
	wstring characterName{ L"Character Name" };;
	wstring description{ L"character description" };;
};