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
    TextPrompt(Screen& screen, int16 posX, int16 posY);
    ~TextPrompt() = default;

private:
    const uint16 DELAY_MS = 0; //500
    const uint8 MAX_LINE = 25;

public:
    void Enqueue(const wstring& msg);
    void Update();                     
    void Render();
    void Clear();

private:
    Screen& m_screen;
    int16 m_posX;
    int16 m_posY;

    deque<wstring> m_waitMessageQueue;
    deque<wstring> m_printMessageQueue;

    unsigned long m_lastPrintTime = 0;
};