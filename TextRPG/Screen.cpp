#include "Screen.h"
#include <iostream>
#include <cwchar>

Screen::Screen()
	: m_writeBuffer(nullptr), m_consoleBufferIndex(0)
{
	SetConsoleOutputCP(CP_UTF8);

	for (int i = 0; i < 2; ++i)
	{
		m_consoleBuffers[i] = CreateConsoleScreenBuffer(
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

	m_writeBuffer = new wchar_t[BUFFER_SIZE];
	Clear();

	VisibleConsoleCursor(false);
}

Screen::~Screen()
{
	for (int i = 0; i < 2; ++i)
	{
		CloseHandle(m_consoleBuffers[i]);
	}

	delete[] m_writeBuffer;
}

void Screen::Write(const int16 x, const int16 y, const std::wstring& text)
{
	if (m_writeBuffer == nullptr)
	{
		return;
	}

	if (x < WIDTH && y < HEIGHT)
	{
		int32 pos = y * WIDTH + x;
		for (size_t i = 0; i < text.size(); i++)
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
	DWORD written = 0;

	for (int32 i = 0; i < BUFFER_SIZE; i++)
	{
		COORD coord = { (SHORT)(i % WIDTH), (SHORT)(i / WIDTH) };
		if (coord.X > WIDTH - 1 || coord.Y > HEIGHT - 1)
		{
			continue;
		}

		WriteConsoleOutputCharacterW(
			m_consoleBuffers[m_consoleBufferIndex],
			&m_writeBuffer[i],
			1,
			coord,
			&written
		);
	}

	SetConsoleActiveScreenBuffer(m_consoleBuffers[m_consoleBufferIndex]);
	m_consoleBufferIndex = m_consoleBufferIndex == 1 ? 0 : 1;
}

void Screen::Clear()
{
	std::fill(m_writeBuffer, m_writeBuffer + BUFFER_SIZE, L' ');
}

void Screen::VisibleConsoleCursor(bool isVisible)
{
	for (int i = 0; i < 2; ++i)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(m_consoleBuffers[i], &cursorInfo);

		cursorInfo.bVisible = isVisible;
		SetConsoleCursorInfo(m_consoleBuffers[i], &cursorInfo);
	}
}

uint8 Screen::GetCharWidth(wchar_t wch)
{
	if (wch >= 0xAC00 && wch <= 0xD7A3)
	{
		return 2;
	}

	return 1;
}
