#pragma once
#include <memory>
#include <string>
#include <windows.h>

class Screen
{
public:
	Screen();
	~Screen();

private:
	const SHORT width = 128;
	const SHORT height = 32;
	const uint32_t bufferSize = width * height;

private:
	HANDLE consoleBuffers[2];
	uint8_t bufferIndex = 0;
	std::unique_ptr<wchar_t[]> buffer = nullptr;

public:
	void Write(const SHORT x, const SHORT y, const std::wstring& text);
	void Render();
	void Clear();

	void ShowConsoleCursor(bool bIsShow);
};
