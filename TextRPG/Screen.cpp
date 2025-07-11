#include "Screen.h"
#include <iostream>
#include <cwchar>

Screen::Screen()
	: WIDTH(128), HEIGHT(32), BUFFER_SIZE(WIDTH* HEIGHT), m_consoleBufferIndex(0), m_writeBuffer(nullptr)
{
	Init();
}

Screen::Screen(int16 width, int16 height)
	: WIDTH(width), HEIGHT(height), BUFFER_SIZE(WIDTH* HEIGHT), m_consoleBufferIndex(0), m_writeBuffer(nullptr)
{
	Init();
}

Screen::~Screen()
{
	Release();
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
		for (size_t i = 0; i < text.size(); ++i)
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

	for (int32 i = 0; i < BUFFER_SIZE; ++i)
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
	m_consoleBufferIndex = 1 - m_consoleBufferIndex;
}

void Screen::Clear()
{
	std::fill(m_writeBuffer, m_writeBuffer + BUFFER_SIZE, L' ');
}

void Screen::VisibleConsoleCursor(const bool isVisible)
{
	for (uint8 i = 0; i < MAX_BUFFER_NUM; ++i)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(m_consoleBuffers[i], &cursorInfo);

		cursorInfo.bVisible = isVisible;
		SetConsoleCursorInfo(m_consoleBuffers[i], &cursorInfo);
	}
}

void Screen::Init()
{
	SetConsoleOutputCP(CP_UTF8);

	for (uint8 i = 0; i < MAX_BUFFER_NUM; ++i)
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

void Screen::Release()
{
	for (int i = 0; i < MAX_BUFFER_NUM; ++i)
	{
		CloseHandle(m_consoleBuffers[i]);
	}

	delete[] m_writeBuffer;
}

uint8 Screen::GetCharWidth(const wchar_t wch)
{
	if (wch >= (int)0xAC00 && wch <= (int)0xD7A3)
	{
		return 2;
	}

	return 1;
}
