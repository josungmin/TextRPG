#include "Screen.h"
#include <cassert>

Screen::Screen()
	: buffer(nullptr)
{
	for (int i = 0; i < 2; ++i)
	{
		consoleBuffers[i] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0, nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);
		SetConsoleScreenBufferSize(consoleBuffers[i], { width, height });

		SMALL_RECT rect = { 
			0, 
			0, 
			width - 1, 
			height - 1 
		};
		SetConsoleWindowInfo(consoleBuffers[i], TRUE, &rect);
	}

	buffer = std::make_unique<wchar_t[]>(bufferSize);
	Clear();

	ShowConsoleCursor(false);
}

Screen::~Screen()
{
	for (int i = 0; i < 2; ++i)
	{
		CloseHandle(consoleBuffers[i]);
	}
}

void Screen::Write(const SHORT x, const SHORT y, const std::wstring& text)
{
	int pos = y * width + x;
	wmemcpy(buffer.get() + pos, text.c_str(), text.size());
}

void Screen::Render()
{
	DWORD written;
	WriteConsoleOutputCharacterW(
		consoleBuffers[bufferIndex], 
		buffer.get(), 
		bufferSize, 
		{ 0, 0 }, 
		&written
	);

	SetConsoleActiveScreenBuffer(consoleBuffers[bufferIndex]);
	bufferIndex = 1 - bufferIndex;
}

void Screen::Clear()
{
	std::fill(buffer.get(), buffer.get() + bufferSize, L' ');
}

void Screen::ShowConsoleCursor(bool bIsShow)
{
	for (int i = 0; i < 2; ++i)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(consoleBuffers[i], &cursorInfo);

		cursorInfo.bVisible = bIsShow;
		SetConsoleCursorInfo(consoleBuffers[i], &cursorInfo);
	}
}
