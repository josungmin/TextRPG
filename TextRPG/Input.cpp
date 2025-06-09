#include "Input.h"
#include "Screen.h"
#include <conio.h>

Input::Input()
{

}

Input::~Input()
{
}

void Input::InputProcess()
{
	while (_kbhit())
	{
		wchar_t ch = _getwch();

		if (ch == L'\r') // Enter
		{
			if (!inputBuffer.empty())
			{
				command = inputBuffer;
				inputBuffer.clear();
			}
		}
		else if (ch == L'\b') // Backspace
		{
			if (!inputBuffer.empty())
			{
				inputBuffer.pop_back();
			}				
		}
		else
		{
			inputBuffer += ch;
		}
	}
}

bool Input::HasCommand()
{
	return !command.empty();
}

wstring Input::GetCommand()
{
	wstring cmd = command;
	command.clear();

	return cmd;
}

