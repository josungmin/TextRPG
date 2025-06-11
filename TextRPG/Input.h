#pragma once
#include <string>

using namespace std;

class Input
{
public:
	Input() = default;
	~Input() = default;

public:
	void InputProcess();
	const bool HasCommand() const;

	const wstring GetCommand();
	inline const wstring& GetInputBuffer() const { return m_inputBuffer; };

private:
	wstring m_inputBuffer;
	wstring m_command;
};