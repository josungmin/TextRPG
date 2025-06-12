#pragma once
#include <memory>
#include <string>
#include <windows.h>

#include "MyType.h"

class Screen
{
public:
	Screen();
	~Screen();

private:
	const SHORT WIDTH = 128;
	const SHORT HEIGHT = 32;
	const int32 BUFFER_SIZE = WIDTH * HEIGHT;

public:
	void Write(const SHORT x, const SHORT y, const std::wstring& text);
	void Render();
	void Clear();

	void ShowConsoleCursor(bool bIsShow);

private:
	uint8 GetCharWidth(wchar_t c);

private:
	HANDLE m_consoleBuffers[2];
	uint8 m_bufferIndex = 0;
	wchar_t* m_buffer = nullptr;
};
