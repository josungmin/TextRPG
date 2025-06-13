#pragma once
#include <string>
#include <windows.h>
#include "MyType.h"

class Screen
{
public:
	Screen();
	Screen(const int16 width, const int16 height);
	~Screen();

	Screen(const Screen& rhs) = delete;
	Screen& operator=(const Screen& rhs) = delete;

private:
	const int16 WIDTH = 128;
	const int16 HEIGHT = 32;
	const int32 BUFFER_SIZE = WIDTH * HEIGHT;

public:
	void Write(const int16 x, const int16 y, const std::wstring& text);
	void Render();
	void Clear();

	void ShowConsoleCursor(bool isShow);

private:
	//bool Init();
	uint8 GetCharWidth(wchar_t c);

private:
	int64 m_consoleBuffers[2];
	uint8 m_consoleBufferIndex = 0;
	wchar_t* m_writeBuffer = nullptr;
};
