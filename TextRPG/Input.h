#pragma once
#include <string>

using namespace std;

class Input
{
public:
	Input();
	~Input();

public:
	void InputProcess();
	bool HasCommand();

	wstring GetCommand();
	inline const wstring& GetInputBuffer() const { return inputBuffer; };

private:
	wstring inputBuffer;
	wstring command;
};