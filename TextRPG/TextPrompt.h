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
    //TextPrompt(int16 posX, int16 posY);
    ~TextPrompt() = default;

private:
    const uint16 DELAY_MS = 0; //500
    const uint8 MAX_LINE = 25;

public:
    void Enqueue(const wstring& msg);
    void Update();                     
    void Render(Screen& m_screen);
    void Clear();

    const bool IsRunning() const { return m_waitMessageQueue.size() != 0; }

private:
    const int16 m_posX = 34;
    const int16 m_posY = 3;

    deque<wstring> m_waitMessageQueue;
    deque<wstring> m_printMessageQueue;

    unsigned long m_lastPrintTime = 0;
};