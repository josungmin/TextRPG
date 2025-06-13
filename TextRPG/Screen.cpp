#include "Screen.h"
#include <iostream>
#include <cwchar>

Screen::Screen()
	: m_writeBuffer(nullptr)
{
	SetConsoleOutputCP(CP_UTF8);

	for (int i = 0; i < 2; ++i)
	{
		m_consoleBuffers[i] = (int64)CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0, nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);
		SetConsoleScreenBufferSize((HANDLE)m_consoleBuffers[i], { WIDTH, HEIGHT });

		SMALL_RECT rect = {
			0,
			0,
			WIDTH - 1,
			HEIGHT - 1
		};
		SetConsoleWindowInfo((HANDLE)m_consoleBuffers[i], TRUE, &rect);
	}

	m_writeBuffer = new wchar_t[HEIGHT * WIDTH];
	Clear();

	ShowConsoleCursor(false);
}

Screen::Screen(const int16 width, const int16 height)
	: WIDTH(width), HEIGHT(height), BUFFER_SIZE(width * height), m_writeBuffer(nullptr)
{
	SetConsoleOutputCP(CP_UTF8);

	for (int i = 0; i < 2; ++i)
	{
		m_consoleBuffers[i] = (int64)CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			0, nullptr,
			CONSOLE_TEXTMODE_BUFFER,
			nullptr
		);
		SetConsoleScreenBufferSize((HANDLE)m_consoleBuffers[i], { WIDTH, HEIGHT });

		SMALL_RECT rect = {
			0,
			0,
			WIDTH - 1,
			HEIGHT - 1
		};
		SetConsoleWindowInfo((HANDLE)m_consoleBuffers[i], TRUE, &rect);
	}

	m_writeBuffer = new wchar_t[HEIGHT * WIDTH];
	Clear();

	ShowConsoleCursor(false);
}

Screen::~Screen()
{
	for (int i = 0; i < 2; ++i)
	{
		CloseHandle((HANDLE)m_consoleBuffers[i]);
	}

	delete[] m_writeBuffer;
}

void Screen::Write(const int16 x, const int16 y, const std::wstring& text)
{
	if (x < WIDTH && y < HEIGHT)
	{
		int pos = y * WIDTH + x;
		for (int i = 0; i < text.size(); i++)
		{
			m_writeBuffer[pos] = text[i];

			if (GetCharWidth(text[i]) == 2)
			{
				m_writeBuffer[++pos] = NULL;
			}

			++pos;
		}	
	}
}

void Screen::Render()
{
	unsigned long written;

	for (int16 i = 0; i < BUFFER_SIZE; i++)
	{
		WriteConsoleOutputCharacterW(
			(HANDLE)m_consoleBuffers[m_consoleBufferIndex],
			&m_writeBuffer[i],
			1,
			{ (int16)(i % WIDTH), (int16)(i / WIDTH) },
			&written
		);
	}

	SetConsoleActiveScreenBuffer((HANDLE)m_consoleBuffers[m_consoleBufferIndex]);
	m_consoleBufferIndex = 1 - m_consoleBufferIndex;
}

void Screen::Clear()
{
	std::fill(m_writeBuffer, m_writeBuffer + BUFFER_SIZE, L' ');
}

void Screen::ShowConsoleCursor(bool bIsShow)
{
	for (int i = 0; i < 2; ++i)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo((HANDLE)m_consoleBuffers[i], &cursorInfo);

		cursorInfo.bVisible = bIsShow;
		SetConsoleCursorInfo((HANDLE)m_consoleBuffers[i], &cursorInfo);
	}
}

uint8 Screen::GetCharWidth(wchar_t c)
{
	if (c >= 0xAC00 && c <= 0xD7A3)
	{
		return 2;
	}

	return 1;
}
