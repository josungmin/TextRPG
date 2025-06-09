#include "TextPrompt.h"

TextPrompt::TextPrompt(Screen& screen, uint8_t posX, uint8_t posY)
	:screen(screen), posX(posX), posY(posY)
{

}

TextPrompt::~TextPrompt()
{

}

void TextPrompt::Enqueue(const std::wstring& msg)
{
	inputMessageQueue.push_back(msg);
}

void TextPrompt::Update()
{
    DWORD now = GetTickCount();

    if (!inputMessageQueue.empty() && (now - lastPrintTime >= delayMS))
    {
        outputMessageQueue.push_back(inputMessageQueue.front());
        inputMessageQueue.pop_front();
        lastPrintTime = now;

        if (outputMessageQueue.size() > maxLines)
        {
            outputMessageQueue.pop_front();
        }
    }
}

void TextPrompt::Render()
{
    uint8_t y = posY;
    for (const auto& msg : outputMessageQueue)
    {
        screen.Write(posX, y++, msg);
    }
}

void TextPrompt::Clear()
{
    inputMessageQueue.clear();
    outputMessageQueue.clear();
}
