#include "TextPrompt.h"
#include "Screen.h"


TextPrompt::TextPrompt()
	:m_posX(34), m_posY(3)
{
	m_lastPrintTime = 0;
}

void TextPrompt::Enqueue(const wstring& message)
{
	m_waitingMessageQueue.push_back(message);
}

void TextPrompt::Update()
{
	DWORD currentTime = GetTickCount();

	if (m_waitingMessageQueue.empty() == false && (currentTime - m_lastPrintTime >= DELAY_MS))
	{
		m_printingMessageQueue.push_back(m_waitingMessageQueue.front());
		m_waitingMessageQueue.pop_front();
		m_lastPrintTime = currentTime;

		if (m_printingMessageQueue.size() * 2 - 1 > MAX_LINE)
		{
			m_printingMessageQueue.pop_front();
		}
	}
}

void TextPrompt::Render(Screen& m_screen)
{
	int16 y = m_posY;
	for (const wstring& message : m_printingMessageQueue)
	{
		m_screen.Write(m_posX, y, message);
		y += 2;
	}
}

void TextPrompt::Clear()
{
	m_waitingMessageQueue.clear();
	m_printingMessageQueue.clear();
}
