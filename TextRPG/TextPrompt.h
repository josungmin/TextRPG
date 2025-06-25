#pragma once
#include <string>
#include <deque>
#include <windows.h>
#include "MyType.h"

using namespace std;

class Screen;

constexpr uint16 DELAY_MS = 0;
constexpr uint16 MAX_LINE = 25;

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

    inline const bool IsRunning() const { return m_waitingMessageQueue.size() != 0; }

private:
    const int16 m_posX = 34;
    const int16 m_posY = 3;

	DWORD m_lastPrintTime;

    deque<wstring> m_waitingMessageQueue;
    deque<wstring> m_printingMessageQueue;
};