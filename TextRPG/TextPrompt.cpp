#include "TextPrompt.h"

TextPrompt::TextPrompt(Screen& screen, uint8_t posX, uint8_t posY)
	:m_screen(screen), m_pivotX(posX), m_pivotY(posY)
{
    
}

void TextPrompt::Enqueue(const std::wstring& msg)
{
	m_inputMessageQueue.push_back(msg);
}

void TextPrompt::Update()
{
    DWORD now = GetTickCount();

    if (!m_inputMessageQueue.empty() && (now - m_lastPrintTime >= DELAY_MS))
    {
        m_outputMessageQueue.push_back(m_inputMessageQueue.front());
        m_inputMessageQueue.pop_front();
        m_lastPrintTime = now;

        if (m_outputMessageQueue.size() > MAX_LINE)
        {
            m_outputMessageQueue.pop_front();
        }
    }
}

void TextPrompt::Render()
{
    uint8_t y = m_pivotY;
    for (const auto& msg : m_outputMessageQueue)
    {
        m_screen.Write(m_pivotX, y++, msg);
    }
}

void TextPrompt::Clear()
{
    m_inputMessageQueue.clear();
    m_outputMessageQueue.clear();
}
