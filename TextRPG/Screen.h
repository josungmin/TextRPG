#pragma once
#include <string>
#include <windows.h>
#include "MyType.h"

constexpr uint8 MAX_BUFFER_NUM = 2;

class Screen
{
public:
	Screen();
	Screen(int16 width, int16 height);
	virtual ~Screen();

public:
	void Write(const int16 x, const int16 y, const std::wstring& text);
	void Render();
	void Clear();

	void VisibleConsoleCursor(const bool isVisible);

private:
	void Init();
	void Release();
	uint8 GetCharWidth(const wchar_t wch);
	 
private:
	const int16 WIDTH = 128;
	const int16 HEIGHT = 32;
	const int32 BUFFER_SIZE = WIDTH * HEIGHT;

private:
	HANDLE m_consoleBuffers[MAX_BUFFER_NUM];
	uint8 m_consoleBufferIndex = 0;
	wchar_t* m_writeBuffer = nullptr;
};
