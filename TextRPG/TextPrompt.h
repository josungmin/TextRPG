#pragma once
#include <string>
#include <deque>
#include <windows.h>
#include "Screen.h"

using namespace std;

class TextPrompt
{
public:
    TextPrompt(Screen& screen, uint8_t posX, uint8_t posY);
    ~TextPrompt() = default;

    void Enqueue(const wstring& msg);
    void Update();                     
    void Render();
    void Clear();

private:
    const uint16_t DELAY_MS = 1000; //2√ 
    const uint8_t MAX_LINE = 24;

    Screen& m_screen;
    uint8_t m_pivotX;
    uint8_t m_pivotY;

    deque<wstring> m_inputMessageQueue;
    deque<wstring> m_outputMessageQueue;

    DWORD m_lastPrintTime = 0;
    bool m_readyToPrint = true;
};