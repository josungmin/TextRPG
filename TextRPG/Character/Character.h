#pragma once
#include <string>
#include <vector>

using namespace std;

class Character
{
public:
	Character(const wstring& characterName, const wstring& description)
		:m_characterName(characterName), m_description(description) { }
	virtual ~Character() = default;

public:
	inline const wstring& GetName() const { return m_characterName; }
	inline const wstring& GetDescription() const { return m_description; }

protected:
	wstring m_characterName{ L"Character Name" };;
	wstring m_description{ L"character description" };;
};