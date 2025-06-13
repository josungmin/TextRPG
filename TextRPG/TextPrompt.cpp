#include "TextPrompt.h"

TextPrompt::TextPrompt()
	:m_posX(34), m_posY(3)
{
}

void TextPrompt::Enqueue(const wstring& msg)
{
	m_waitMessageQueue.push_back(msg);
}

void TextPrompt::Update()
{
	const uint32 currentTime = GetTickCount();

	if (m_waitMessageQueue.empty() == false && (currentTime - m_lastPrintTime >= DELAY_MS))
	{
		m_printMessageQueue.push_back(m_waitMessageQueue.front());
		m_waitMessageQueue.pop_front();
		m_lastPrintTime = currentTime;

		if (m_printMessageQueue.size() * 2 - 1 > MAX_LINE)
		{
			m_printMessageQueue.pop_front();
		}
	}
}

void TextPrompt::Render(Screen& m_screen)
{
	int16 y = m_posY;
	for (const wstring& msg : m_printMessageQueue)
	{
		m_screen.Write(m_posX, y, msg);
		y += 2;
	}
}

void TextPrompt::Clear()
{
	m_waitMessageQueue.clear();
	m_printMessageQueue.clear();
}
