#include "Input.h"
#include <conio.h>

void Input::InputProcess()
{
	while (_kbhit())
	{
		wchar_t ch = _getwch();

		if (ch == L'\r') // Enter
		{
			if (m_inputBuffer.empty() == false)
			{
				m_command = m_inputBuffer;
				m_inputBuffer.clear();
			}
		}
		else if (ch == L'\b') // Backspace
		{
			if (m_inputBuffer.empty() == false)
			{
				m_inputBuffer.pop_back();
			}				
		}
		else
		{
			m_inputBuffer += ch;
		}
	}
}

const bool Input::HasCommand() const
{
	return m_command.empty() == false;
}

const wstring Input::GetCommand()
{
	wstring cmd = m_command;
	m_command.clear();

	return cmd;
}

