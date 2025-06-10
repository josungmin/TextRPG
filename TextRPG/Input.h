#pragma once
#include <string>

using namespace std;

class Input
{
public:
	Input() = default;
	~Input() = default;
	Input(const Input&) = delete;


public:
	void InputProcess();
	bool HasCommand();

	wstring GetCommand();
	inline const wstring& GetInputBuffer() const { return inputBuffer; };

private:
	wstring inputBuffer;
	wstring command;
};