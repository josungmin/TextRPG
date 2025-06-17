#pragma once
#include <string>

using namespace std;

class Input
{
public:
	Input() = default;
	virtual ~Input() = default;

public:
	void InputProcess();
	const wstring GetCommand();

	inline const bool HasCommand() const { return m_command.empty() == false; }
	inline const wstring& GetInputBuffer() const { return m_inputBuffer; };

private:
	wstring m_inputBuffer;
	wstring m_command;
};