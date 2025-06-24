#include "Input.h"
#include <conio.h>

void Input::InputProcess()
{
	while (_kbhit())
	{
		wchar_t wch = _getwch();

		if (wch == L'\r') // Enter
		{
			if (m_inputBuffer.empty() == false)
			{
				m_command = m_inputBuffer;
				m_inputBuffer.clear();
			}
		}
		else if (wch == L'\b') // Backspace
		{
			if (m_inputBuffer.empty() == false)
			{
				m_inputBuffer.pop_back();
			}				
		}
		else
		{
			m_inputBuffer += wch;
		}
	}
}

const wstring Input::GetCommand()
{
	wstring cmd = m_command;
	m_command.clear();
	return cmd;
}
