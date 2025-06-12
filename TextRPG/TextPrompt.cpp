#include "TextPrompt.h"

TextPrompt::TextPrompt(Screen& screen, uint8_t posX, uint8_t posY)
	:m_screen(screen), m_posX(posX), m_posY(posY)
{
}

void TextPrompt::Enqueue(const wstring& msg)
{
	m_waitMessageQueue.push_back(msg);
}

void TextPrompt::Update()
{
    DWORD now = GetTickCount();

    if (m_waitMessageQueue.empty() == false && (now - m_lastPrintTime >= DELAY_MS))
    {
        m_printMessageQueue.push_back(m_waitMessageQueue.front());
        m_waitMessageQueue.pop_front();
        m_lastPrintTime = now;

        if (m_printMessageQueue.size() > MAX_LINE)
        {
            m_printMessageQueue.pop_front();
        }
    }
}

void TextPrompt::Render()
{
    uint8 y = m_posY;
    for (const wstring& msg : m_printMessageQueue)
    {
        m_screen.Write(m_posX, y++, msg);
    }
}

void TextPrompt::Clear()
{
    m_waitMessageQueue.clear();
    m_printMessageQueue.clear();
}
