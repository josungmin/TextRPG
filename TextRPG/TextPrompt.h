#pragma once
#include <string>
#include <deque>
//#include <windows.h>
#include "MyType.h"
#include "Screen.h"

using namespace std;

class TextPrompt
{
public:
    TextPrompt(Screen& screen, uint8 posX, uint8 posY);
    ~TextPrompt() = default;

private:
    const uint16 DELAY_MS = 500;
    const uint8 MAX_LINE = 25;

public:
    void Enqueue(const wstring& msg);
    void Update();                     
    void Render();
    void Clear();


private:
    Screen& m_screen;
    uint8 m_posX;
    uint8 m_posY;

    deque<wstring> m_waitMessageQueue;
    deque<wstring> m_printMessageQueue;

    unsigned long m_lastPrintTime = 0;
};