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
    ~TextPrompt();

    void Enqueue(const std::wstring& msg);
    void Update();                     
    void Render();
    void Clear();

private:
    Screen& screen;
    uint8_t posX;
    uint8_t posY;

    deque<wstring> inputMessageQueue;
    deque<wstring> outputMessageQueue;

    DWORD lastPrintTime = 0;
    bool readyToPrint = true;

    const uint16_t delayMS = 1000; //2√ 
    const uint8_t maxLines = 24;
};