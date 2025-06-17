#pragma once
#include <string>
#include <deque>
#include "MyType.h"
#include "Screen.h"

using namespace std;

class TextPrompt
{
public:
    TextPrompt();
    virtual ~TextPrompt() = default;

public:
    void Enqueue(const wstring& message);
    void Update();                     
    void Render(Screen& m_screen);
    void Clear();

    inline const bool IsRunning() const { return m_waitMessageQueue.size() != 0; }

private:
    const uint16 DELAY_MS = 0;
    const uint8 MAX_LINE = 25;

private:
    const int16 m_posX = 34;
    const int16 m_posY = 3;

    deque<wstring> m_waitMessageQueue;
    deque<wstring> m_printMessageQueue;

    DWORD m_lastPrintTime = 0;
};