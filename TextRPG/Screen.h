#pragma once
#include <string>
#include <windows.h>
#include "MyType.h"

class Screen
{
public:
	Screen();
	virtual ~Screen();

	Screen(const Screen& rhs) = delete;
	Screen(const Screen&& rhs) = delete;
	Screen& operator=(const Screen& rhs) = delete;
	Screen& operator=(Screen&& rhs) = delete;

public:
	void Write(const int16 x, const int16 y, const std::wstring& text);
	void Render();
	void Clear();

	void VisibleConsoleCursor(bool isVisible);

private:
	uint8 GetCharWidth(wchar_t wch);
	 
private:
	const int16 WIDTH = 128;
	const int16 HEIGHT = 32;
	const int32 BUFFER_SIZE = WIDTH * HEIGHT;

private:
	HANDLE m_consoleBuffers[2];
	uint8 m_consoleBufferIndex = 0;
	wchar_t* m_writeBuffer = nullptr;
};
